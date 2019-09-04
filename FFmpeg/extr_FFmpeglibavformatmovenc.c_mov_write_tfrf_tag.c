#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uuid ;
typedef  int uint8_t ;
struct TYPE_8__ {int ism_lookahead; } ;
struct TYPE_7__ {int nb_frag_info; TYPE_1__* frag_info; } ;
struct TYPE_6__ {int /*<<< orphan*/  duration; int /*<<< orphan*/  time; int /*<<< orphan*/  tfrf_offset; } ;
typedef  TYPE_2__ MOVTrack ;
typedef  TYPE_3__ MOVMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb24 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int const*,int) ; 
 int /*<<< orphan*/  ffio_fill (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int mov_write_tfrf_tag(AVIOContext *pb, MOVMuxContext *mov,
                              MOVTrack *track, int entry)
{
    int n = track->nb_frag_info - 1 - entry, i;
    int size = 8 + 16 + 4 + 1 + 16*n;
    static const uint8_t uuid[] = {
        0xd4, 0x80, 0x7e, 0xf2, 0xca, 0x39, 0x46, 0x95,
        0x8e, 0x54, 0x26, 0xcb, 0x9e, 0x46, 0xa7, 0x9f
    };

    if (entry < 0)
        return 0;

    avio_seek(pb, track->frag_info[entry].tfrf_offset, SEEK_SET);
    avio_wb32(pb, size);
    ffio_wfourcc(pb, "uuid");
    avio_write(pb, uuid, sizeof(uuid));
    avio_w8(pb, 1);
    avio_wb24(pb, 0);
    avio_w8(pb, n);
    for (i = 0; i < n; i++) {
        int index = entry + 1 + i;
        avio_wb64(pb, track->frag_info[index].time);
        avio_wb64(pb, track->frag_info[index].duration);
    }
    if (n < mov->ism_lookahead) {
        int free_size = 16 * (mov->ism_lookahead - n);
        avio_wb32(pb, free_size);
        ffio_wfourcc(pb, "free");
        ffio_fill(pb, 0, free_size - 8);
    }

    return 0;
}