#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_13__ {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_12__ {char* data; int size; int /*<<< orphan*/  pos; } ;
struct TYPE_11__ {int searchstr_len; int /*<<< orphan*/ * searchstr; int /*<<< orphan*/ * boundary; scalar_t__ strict_mime_boundary; } ;
typedef  TYPE_1__ MPJPEGDemuxContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int av_append_packet (int /*<<< orphan*/ ,TYPE_2__*,int const) ; 
 void* av_asprintf (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int av_get_packet (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  av_init_packet (TYPE_2__*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_2__*) ; 
 void* av_strdup (char*) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ ) ; 
 int ffio_ensure_seekback (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  memcmp (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * mpjpeg_get_boundary (int /*<<< orphan*/ ) ; 
 int parse_multipart_header (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mpjpeg_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    int size;
    int ret;

    MPJPEGDemuxContext *mpjpeg = s->priv_data;
    if (mpjpeg->boundary == NULL) {
        uint8_t* boundary = NULL;
        if (mpjpeg->strict_mime_boundary) {
            boundary = mpjpeg_get_boundary(s->pb);
        }
        if (boundary != NULL) {
            mpjpeg->boundary = av_asprintf("--%s", boundary);
            mpjpeg->searchstr = av_asprintf("\r\n--%s\r\n", boundary);
            av_freep(&boundary);
        } else {
            mpjpeg->boundary = av_strdup("--");
            mpjpeg->searchstr = av_strdup("\r\n--");
        }
        if (!mpjpeg->boundary || !mpjpeg->searchstr) {
            av_freep(&mpjpeg->boundary);
            av_freep(&mpjpeg->searchstr);
            return AVERROR(ENOMEM);
        }
        mpjpeg->searchstr_len = strlen(mpjpeg->searchstr);
    }

    ret = parse_multipart_header(s->pb, &size, mpjpeg->boundary, s);


    if (ret < 0)
        return ret;

    if (size > 0) {
        /* size has been provided to us in MIME header */
        ret = av_get_packet(s->pb, pkt, size);
    } else {
        /* no size was given -- we read until the next boundary or end-of-file */
        int remaining = 0, len;

        const int read_chunk = 2048;
        av_init_packet(pkt);
        pkt->data = NULL;
        pkt->size = 0;
        pkt->pos  = avio_tell(s->pb);

        while ((ret = ffio_ensure_seekback(s->pb, read_chunk - remaining)) >= 0 && /* we may need to return as much as all we've read back to the buffer */
               (ret = av_append_packet(s->pb, pkt, read_chunk - remaining)) >= 0) {
            /* scan the new data */
            char *start;

            len = ret + remaining;
            start = pkt->data + pkt->size - len;
            do {
                if (!memcmp(start, mpjpeg->searchstr, mpjpeg->searchstr_len)) {
                    // got the boundary! rewind the stream
                    avio_seek(s->pb, -len, SEEK_CUR);
                    pkt->size -= len;
                    return pkt->size;
                }
                len--;
                start++;
            } while (len >= mpjpeg->searchstr_len);
            remaining = len;
        }

        /* error or EOF occurred */
        if (ret == AVERROR_EOF) {
            ret = pkt->size > 0 ? pkt->size : AVERROR_EOF;
        } else {
            av_packet_unref(pkt);
        }
    }

    return ret;
}