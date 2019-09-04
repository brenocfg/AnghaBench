#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_18__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_22__ {int seekable; } ;
struct TYPE_21__ {int nb_streams; TYPE_18__** streams; TYPE_5__* pb; TYPE_1__* priv_data; } ;
struct TYPE_20__ {int header_state; int sofdec; int dvd; int raw_ac3; } ;
struct TYPE_19__ {int id; } ;
typedef  TYPE_1__ MpegDemuxContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AVINDEX_KEYFRAME ; 
 int AVIO_SEEKABLE_NORMAL ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 scalar_t__ AV_RB32 (int*) ; 
 int FFERROR_REDO ; 
 int MAX_SYNC_SIZE ; 
 int PACK_START_CODE ; 
 int PADDING_STREAM ; 
 int PRIVATE_STREAM_1 ; 
 int PRIVATE_STREAM_2 ; 
 int PROGRAM_STREAM_MAP ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int SYSTEM_HEADER_START_CODE ; 
 int /*<<< orphan*/  av_add_index_entry (TYPE_18__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (int*) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 int* av_malloc (int) ; 
 scalar_t__ avio_feof (TYPE_5__*) ; 
 int avio_r8 (TYPE_5__*) ; 
 int avio_rb16 (TYPE_5__*) ; 
 int avio_read (TYPE_5__*,int*,int) ; 
 int /*<<< orphan*/  avio_seek (TYPE_5__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ avio_skip (TYPE_5__*,int) ; 
 scalar_t__ avio_tell (TYPE_5__*) ; 
 int /*<<< orphan*/  ff_reduce_index (TYPE_2__*,int) ; 
 int ffio_ensure_seekback (TYPE_5__*,int) ; 
 int find_next_start_code (TYPE_5__*,int*,int*) ; 
 scalar_t__ get_pts (TYPE_5__*,int) ; 
 int* memchr (int*,char,int) ; 
 int /*<<< orphan*/  memcmp (int*,char*,int) ; 
 int /*<<< orphan*/  mpegps_psm_parse (TYPE_1__*,TYPE_5__*) ; 

__attribute__((used)) static int mpegps_read_pes_header(AVFormatContext *s,
                                  int64_t *ppos, int *pstart_code,
                                  int64_t *ppts, int64_t *pdts)
{
    MpegDemuxContext *m = s->priv_data;
    int len, size, startcode, c, flags, header_len;
    int pes_ext, ext2_len, id_ext, skip;
    int64_t pts, dts;
    int64_t last_sync = avio_tell(s->pb);

error_redo:
    avio_seek(s->pb, last_sync, SEEK_SET);
redo:
    /* next start code (should be immediately after) */
    m->header_state = 0xff;
    size      = MAX_SYNC_SIZE;
    startcode = find_next_start_code(s->pb, &size, &m->header_state);
    last_sync = avio_tell(s->pb);
    if (startcode < 0) {
        if (avio_feof(s->pb))
            return AVERROR_EOF;
        // FIXME we should remember header_state
        return FFERROR_REDO;
    }

    if (startcode == PACK_START_CODE)
        goto redo;
    if (startcode == SYSTEM_HEADER_START_CODE)
        goto redo;
    if (startcode == PADDING_STREAM) {
        avio_skip(s->pb, avio_rb16(s->pb));
        goto redo;
    }
    if (startcode == PRIVATE_STREAM_2) {
        if (!m->sofdec) {
            /* Need to detect whether this from a DVD or a 'Sofdec' stream */
            int len = avio_rb16(s->pb);
            int bytesread = 0;
            uint8_t *ps2buf = av_malloc(len);

            if (ps2buf) {
                bytesread = avio_read(s->pb, ps2buf, len);

                if (bytesread != len) {
                    avio_skip(s->pb, len - bytesread);
                } else {
                    uint8_t *p = 0;
                    if (len >= 6)
                        p = memchr(ps2buf, 'S', len - 5);

                    if (p)
                        m->sofdec = !memcmp(p+1, "ofdec", 5);

                    m->sofdec -= !m->sofdec;

                    if (m->sofdec < 0) {
                        if (len == 980  && ps2buf[0] == 0) {
                            /* PCI structure? */
                            uint32_t startpts = AV_RB32(ps2buf + 0x0d);
                            uint32_t endpts = AV_RB32(ps2buf + 0x11);
                            uint8_t hours = ((ps2buf[0x19] >> 4) * 10) + (ps2buf[0x19] & 0x0f);
                            uint8_t mins  = ((ps2buf[0x1a] >> 4) * 10) + (ps2buf[0x1a] & 0x0f);
                            uint8_t secs  = ((ps2buf[0x1b] >> 4) * 10) + (ps2buf[0x1b] & 0x0f);

                            m->dvd = (hours <= 23 &&
                                      mins  <= 59 &&
                                      secs  <= 59 &&
                                      (ps2buf[0x19] & 0x0f) < 10 &&
                                      (ps2buf[0x1a] & 0x0f) < 10 &&
                                      (ps2buf[0x1b] & 0x0f) < 10 &&
                                      endpts >= startpts);
                        } else if (len == 1018 && ps2buf[0] == 1) {
                            /* DSI structure? */
                            uint8_t hours = ((ps2buf[0x1d] >> 4) * 10) + (ps2buf[0x1d] & 0x0f);
                            uint8_t mins  = ((ps2buf[0x1e] >> 4) * 10) + (ps2buf[0x1e] & 0x0f);
                            uint8_t secs  = ((ps2buf[0x1f] >> 4) * 10) + (ps2buf[0x1f] & 0x0f);

                            m->dvd = (hours <= 23 &&
                                      mins  <= 59 &&
                                      secs  <= 59 &&
                                      (ps2buf[0x1d] & 0x0f) < 10 &&
                                      (ps2buf[0x1e] & 0x0f) < 10 &&
                                      (ps2buf[0x1f] & 0x0f) < 10);
                        }
                    }
                }

                av_free(ps2buf);

                /* If this isn't a DVD packet or no memory
                 * could be allocated, just ignore it.
                 * If we did, move back to the start of the
                 * packet (plus 'length' field) */
                if (!m->dvd || avio_skip(s->pb, -(len + 2)) < 0) {
                    /* Skip back failed.
                     * This packet will be lost but that can't be helped
                     * if we can't skip back
                     */
                    goto redo;
                }
            } else {
                /* No memory */
                avio_skip(s->pb, len);
                goto redo;
            }
        } else if (!m->dvd) {
            int len = avio_rb16(s->pb);
            avio_skip(s->pb, len);
            goto redo;
        }
    }
    if (startcode == PROGRAM_STREAM_MAP) {
        mpegps_psm_parse(m, s->pb);
        goto redo;
    }

    /* find matching stream */
    if (!((startcode >= 0x1c0 && startcode <= 0x1df) ||
          (startcode >= 0x1e0 && startcode <= 0x1ef) ||
          (startcode == 0x1bd) ||
          (startcode == PRIVATE_STREAM_2) ||
          (startcode == 0x1fd)))
        goto redo;
    if (ppos) {
        *ppos = avio_tell(s->pb) - 4;
    }
    len = avio_rb16(s->pb);
    pts =
    dts = AV_NOPTS_VALUE;
    if (startcode != PRIVATE_STREAM_2)
    {
    /* stuffing */
    for (;;) {
        if (len < 1)
            goto error_redo;
        c = avio_r8(s->pb);
        len--;
        /* XXX: for MPEG-1, should test only bit 7 */
        if (c != 0xff)
            break;
    }
    if ((c & 0xc0) == 0x40) {
        /* buffer scale & size */
        avio_r8(s->pb);
        c    = avio_r8(s->pb);
        len -= 2;
    }
    if ((c & 0xe0) == 0x20) {
        dts  =
        pts  = get_pts(s->pb, c);
        len -= 4;
        if (c & 0x10) {
            dts  = get_pts(s->pb, -1);
            len -= 5;
        }
    } else if ((c & 0xc0) == 0x80) {
        /* mpeg 2 PES */
        flags      = avio_r8(s->pb);
        header_len = avio_r8(s->pb);
        len       -= 2;
        if (header_len > len)
            goto error_redo;
        len -= header_len;
        if (flags & 0x80) {
            dts         = pts = get_pts(s->pb, -1);
            header_len -= 5;
            if (flags & 0x40) {
                dts         = get_pts(s->pb, -1);
                header_len -= 5;
            }
        }
        if (flags & 0x3f && header_len == 0) {
            flags &= 0xC0;
            av_log(s, AV_LOG_WARNING, "Further flags set but no bytes left\n");
        }
        if (flags & 0x01) { /* PES extension */
            pes_ext = avio_r8(s->pb);
            header_len--;
            /* Skip PES private data, program packet sequence counter
             * and P-STD buffer */
            skip  = (pes_ext >> 4) & 0xb;
            skip += skip & 0x9;
            if (pes_ext & 0x40 || skip > header_len) {
                av_log(s, AV_LOG_WARNING, "pes_ext %X is invalid\n", pes_ext);
                pes_ext = skip = 0;
            }
            avio_skip(s->pb, skip);
            header_len -= skip;

            if (pes_ext & 0x01) { /* PES extension 2 */
                ext2_len = avio_r8(s->pb);
                header_len--;
                if ((ext2_len & 0x7f) > 0) {
                    id_ext = avio_r8(s->pb);
                    if ((id_ext & 0x80) == 0)
                        startcode = ((startcode & 0xff) << 8) | id_ext;
                    header_len--;
                }
            }
        }
        if (header_len < 0)
            goto error_redo;
        avio_skip(s->pb, header_len);
    } else if (c != 0xf)
        goto redo;
    }

    if (startcode == PRIVATE_STREAM_1) {
        int ret = ffio_ensure_seekback(s->pb, 2);

        if (ret < 0)
            return ret;

        startcode = avio_r8(s->pb);
        m->raw_ac3 = 0;
        if (startcode == 0x0b) {
            if (avio_r8(s->pb) == 0x77) {
                startcode = 0x80;
                m->raw_ac3 = 1;
                avio_skip(s->pb, -2);
            } else {
                avio_skip(s->pb, -1);
            }
        } else {
            len--;
        }
    }
    if (len < 0)
        goto error_redo;
    if (dts != AV_NOPTS_VALUE && ppos) {
        int i;
        for (i = 0; i < s->nb_streams; i++) {
            if (startcode == s->streams[i]->id &&
                (s->pb->seekable & AVIO_SEEKABLE_NORMAL) /* index useless on streams anyway */) {
                ff_reduce_index(s, i);
                av_add_index_entry(s->streams[i], *ppos, dts, 0, 0,
                                   AVINDEX_KEYFRAME /* FIXME keyframe? */);
            }
        }
    }

    *pstart_code = startcode;
    *ppts        = pts;
    *pdts        = dts;
    return len;
}