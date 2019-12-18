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
struct TYPE_6__ {int error; int position; int length; int sector_bits; int nb_sectors; scalar_t__* sectors; TYPE_2__* pb_filesystem; } ;
typedef  TYPE_1__ WtvFile ;
struct TYPE_7__ {scalar_t__ error; } ;
typedef  TYPE_2__ AVIOContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int FFMIN (int,int) ; 
 int WTV_SECTOR_BITS ; 
 scalar_t__ avio_feof (TYPE_2__*) ; 
 int avio_read (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ seek_by_sector (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wtvfile_read_packet(void *opaque, uint8_t *buf, int buf_size)
{
    WtvFile *wf = opaque;
    AVIOContext *pb = wf->pb_filesystem;
    int nread = 0;

    if (wf->error || pb->error)
        return -1;
    if (wf->position >= wf->length || avio_feof(pb))
        return AVERROR_EOF;

    buf_size = FFMIN(buf_size, wf->length - wf->position);
    while(nread < buf_size) {
        int n;
        int remaining_in_sector = (1 << wf->sector_bits) - (wf->position & ((1 << wf->sector_bits) - 1));
        int read_request        = FFMIN(buf_size - nread, remaining_in_sector);

        n = avio_read(pb, buf, read_request);
        if (n <= 0)
            break;
        nread += n;
        buf += n;
        wf->position += n;
        if (n == remaining_in_sector) {
            int i = wf->position >> wf->sector_bits;
            if (i >= wf->nb_sectors ||
                (wf->sectors[i] != wf->sectors[i - 1] + (1 << (wf->sector_bits - WTV_SECTOR_BITS)) &&
                seek_by_sector(pb, wf->sectors[i], 0) < 0)) {
                wf->error = 1;
                break;
            }
        }
    }
    return nread;
}