#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_6__ {unsigned int nb_samples; int /*<<< orphan*/ * seek_table; } ;
typedef  TYPE_1__ TTAMuxContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 unsigned int UINT32_MAX ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int avio_close_dyn_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_ape_write_tag (TYPE_2__*) ; 
 unsigned int ffio_get_checksum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tta_queue_flush (TYPE_2__*) ; 

__attribute__((used)) static int tta_write_trailer(AVFormatContext *s)
{
    TTAMuxContext *tta = s->priv_data;
    uint8_t *ptr;
    unsigned int crc;
    int size;

    avio_wl32(s->pb, tta->nb_samples);
    crc = ffio_get_checksum(s->pb) ^ UINT32_MAX;
    avio_wl32(s->pb, crc);

    /* Write Seek table */
    crc = ffio_get_checksum(tta->seek_table) ^ UINT32_MAX;
    avio_wl32(tta->seek_table, crc);
    size = avio_close_dyn_buf(tta->seek_table, &ptr);
    avio_write(s->pb, ptr, size);
    tta->seek_table = NULL;
    av_free(ptr);

    /* Write audio data */
    tta_queue_flush(s);

    ff_ape_write_tag(s);
    avio_flush(s->pb);

    return 0;
}