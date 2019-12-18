#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int64_t ;
struct TYPE_6__ {int (* io_open ) (TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * pb; int /*<<< orphan*/  url; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVIO_FLAG_READ ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  READ_BLOCK ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * av_malloc (int) ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_format_io_close (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int shift_data(AVFormatContext *format_context, int64_t shift_size)
{
    int ret = 0;
    int64_t pos, pos_end = avio_tell(format_context->pb);
    uint8_t *buf, *read_buf[2];
    int read_buf_id = 0;
    int read_size[2];
    AVIOContext *read_pb;

    buf = av_malloc(shift_size * 2);
    if (!buf)
        return AVERROR(ENOMEM);
    read_buf[0] = buf;
    read_buf[1] = buf + shift_size;

    /* Write the header at the beginning of the file, shifting all content as necessary;
     * based on the approach used by MOV faststart. */
    avio_flush(format_context->pb);
    ret = format_context->io_open(format_context, &read_pb, format_context->url, AVIO_FLAG_READ, NULL);
    if (ret < 0) {
        av_log(format_context, AV_LOG_ERROR, "Unable to re-open %s output file to "
               "write the header\n", format_context->url);
        av_free(buf);
        return ret;
    }

    /* mark the end of the shift to up to the last data we wrote, and get ready
     * for writing */
    pos_end = avio_tell(format_context->pb);
    avio_seek(format_context->pb, shift_size, SEEK_SET);

    /* start reading at where the new header will be placed */
    avio_seek(read_pb, 0, SEEK_SET);
    pos = avio_tell(read_pb);

#define READ_BLOCK do {                                                             \
    read_size[read_buf_id] = avio_read(read_pb, read_buf[read_buf_id], shift_size);  \
    read_buf_id ^= 1;                                                               \
} while (0)

    /* shift data by chunk of at most shift_size */
    READ_BLOCK;
    do {
        int n;
        READ_BLOCK;
        n = read_size[read_buf_id];
        if (n <= 0)
            break;
        avio_write(format_context->pb, read_buf[read_buf_id], n);
        pos += n;
    } while (pos < pos_end);
    ff_format_io_close(format_context, &read_pb);

    av_free(buf);
    return 0;
}