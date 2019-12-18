#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_11__ {int /*<<< orphan*/ * pb; TYPE_1__** streams; } ;
struct TYPE_10__ {size_t stream_index; int flags; int segments_count; int size; int /*<<< orphan*/ * data; int /*<<< orphan*/ * segments; int /*<<< orphan*/  granule; } ;
struct TYPE_9__ {int /*<<< orphan*/  page_count; int /*<<< orphan*/  page_counter; int /*<<< orphan*/  serial_num; } ;
struct TYPE_8__ {TYPE_2__* priv_data; } ;
typedef  TYPE_2__ OGGStreamContext ;
typedef  TYPE_3__ OGGPage ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int avio_close_dyn_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ *) ; 
 int avio_open_dyn_buf (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wl64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_crc04C11DB7_update ; 
 int /*<<< orphan*/  ffio_init_checksum (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ogg_update_checksum (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ogg_write_page(AVFormatContext *s, OGGPage *page, int extra_flags)
{
    OGGStreamContext *oggstream = s->streams[page->stream_index]->priv_data;
    AVIOContext *pb;
    int64_t crc_offset;
    int ret, size;
    uint8_t *buf;

    ret = avio_open_dyn_buf(&pb);
    if (ret < 0)
        return ret;
    ffio_init_checksum(pb, ff_crc04C11DB7_update, 0);
    ffio_wfourcc(pb, "OggS");
    avio_w8(pb, 0);
    avio_w8(pb, page->flags | extra_flags);
    avio_wl64(pb, page->granule);
    avio_wl32(pb, oggstream->serial_num);
    avio_wl32(pb, oggstream->page_counter++);
    crc_offset = avio_tell(pb);
    avio_wl32(pb, 0); // crc
    avio_w8(pb, page->segments_count);
    avio_write(pb, page->segments, page->segments_count);
    avio_write(pb, page->data, page->size);

    ogg_update_checksum(s, pb, crc_offset);
    avio_flush(pb);

    size = avio_close_dyn_buf(pb, &buf);
    if (size < 0)
        return size;

    avio_write(s->pb, buf, size);
    avio_flush(s->pb);
    av_free(buf);
    oggstream->page_count--;
    return 0;
}