#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ogg_stream {int page_pos; scalar_t__ psize; char* segments; int nsegs; int segp; int got_data; int pstart; int sync_pos; int bufsize; int bufpos; char* buf; int flags; int /*<<< orphan*/  granule; scalar_t__ incomplete; } ;
struct ogg {int page_pos; struct ogg_stream* streams; } ;
struct TYPE_16__ {struct ogg* priv_data; TYPE_1__* pb; } ;
struct TYPE_15__ {int seekable; } ;
typedef  TYPE_1__ AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 int AVIO_SEEKABLE_NORMAL ; 
 int AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int MAX_PAGE_SIZE ; 
 int OGG_FLAG_BOS ; 
 int OGG_FLAG_CONT ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 char* av_malloc (int) ; 
 scalar_t__ avio_feof (TYPE_1__*) ; 
 int avio_r8 (TYPE_1__*) ; 
 int avio_read (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  avio_rl32 (TYPE_1__*) ; 
 int /*<<< orphan*/  avio_rl64 (TYPE_1__*) ; 
 int /*<<< orphan*/  avio_seek (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (TYPE_1__*,int) ; 
 int avio_tell (TYPE_1__*) ; 
 scalar_t__ data_packets_seen (struct ogg*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int ogg_find_stream (struct ogg*,int /*<<< orphan*/ ) ; 
 int ogg_new_buf (struct ogg*,int) ; 
 int ogg_new_stream (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int ogg_replace_stream (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ogg_read_page(AVFormatContext *s, int *sid)
{
    AVIOContext *bc = s->pb;
    struct ogg *ogg = s->priv_data;
    struct ogg_stream *os;
    int ret, i = 0;
    int flags, nsegs;
    uint64_t gp;
    uint32_t serial;
    int size, idx;
    uint8_t sync[4];
    int sp = 0;

    ret = avio_read(bc, sync, 4);
    if (ret < 4)
        return ret < 0 ? ret : AVERROR_EOF;

    do {
        int c;

        if (sync[sp & 3] == 'O' &&
            sync[(sp + 1) & 3] == 'g' &&
            sync[(sp + 2) & 3] == 'g' && sync[(sp + 3) & 3] == 'S')
            break;

        if(!i && (bc->seekable & AVIO_SEEKABLE_NORMAL) && ogg->page_pos > 0) {
            memset(sync, 0, 4);
            avio_seek(bc, ogg->page_pos+4, SEEK_SET);
            ogg->page_pos = -1;
        }

        c = avio_r8(bc);

        if (avio_feof(bc))
            return AVERROR_EOF;

        sync[sp++ & 3] = c;
    } while (i++ < MAX_PAGE_SIZE);

    if (i >= MAX_PAGE_SIZE) {
        av_log(s, AV_LOG_INFO, "cannot find sync word\n");
        return AVERROR_INVALIDDATA;
    }

    if (avio_r8(bc) != 0) {      /* version */
        av_log (s, AV_LOG_ERROR, "ogg page, unsupported version\n");
        return AVERROR_INVALIDDATA;
    }

    flags  = avio_r8(bc);
    gp     = avio_rl64(bc);
    serial = avio_rl32(bc);
    avio_skip(bc, 8); /* seq, crc */
    nsegs  = avio_r8(bc);

    idx = ogg_find_stream(ogg, serial);
    if (idx < 0) {
        if (data_packets_seen(ogg))
            idx = ogg_replace_stream(s, serial, nsegs);
        else
            idx = ogg_new_stream(s, serial);

        if (idx < 0) {
            av_log(s, AV_LOG_ERROR, "failed to create or replace stream\n");
            return idx;
        }
    }

    os = ogg->streams + idx;
    ogg->page_pos =
    os->page_pos = avio_tell(bc) - 27;

    if (os->psize > 0) {
        ret = ogg_new_buf(ogg, idx);
        if (ret < 0)
            return ret;
    }

    ret = avio_read(bc, os->segments, nsegs);
    if (ret < nsegs)
        return ret < 0 ? ret : AVERROR_EOF;

    os->nsegs = nsegs;
    os->segp  = 0;

    size = 0;
    for (i = 0; i < nsegs; i++)
        size += os->segments[i];

    if (!(flags & OGG_FLAG_BOS))
        os->got_data = 1;

    if (flags & OGG_FLAG_CONT || os->incomplete) {
        if (!os->psize) {
            // If this is the very first segment we started
            // playback in the middle of a continuation packet.
            // Discard it since we missed the start of it.
            while (os->segp < os->nsegs) {
                int seg = os->segments[os->segp++];
                os->pstart += seg;
                if (seg < 255)
                    break;
            }
            os->sync_pos = os->page_pos;
        }
    } else {
        os->psize    = 0;
        os->sync_pos = os->page_pos;
    }

    if (os->bufsize - os->bufpos < size) {
        uint8_t *nb = av_malloc((os->bufsize *= 2) + AV_INPUT_BUFFER_PADDING_SIZE);
        if (!nb)
            return AVERROR(ENOMEM);
        memcpy(nb, os->buf, os->bufpos);
        av_free(os->buf);
        os->buf = nb;
    }

    ret = avio_read(bc, os->buf + os->bufpos, size);
    if (ret < size)
        return ret < 0 ? ret : AVERROR_EOF;

    os->bufpos += size;
    os->granule = gp;
    os->flags   = flags;

    memset(os->buf + os->bufpos, 0, AV_INPUT_BUFFER_PADDING_SIZE);
    if (sid)
        *sid = idx;

    return 0;
}