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
struct TYPE_8__ {int size; scalar_t__ data; } ;
struct TYPE_7__ {size_t entry; int /*<<< orphan*/  has_keyframes; TYPE_1__* cluster; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ MOVTrack ;
typedef  TYPE_3__ AVPacket ;

/* Variables and functions */
 int AV_RB16 (scalar_t__) ; 
 int AV_RB32 (scalar_t__) ; 
 int /*<<< orphan*/  MOV_SYNC_SAMPLE ; 

__attribute__((used)) static void mov_parse_truehd_frame(AVPacket *pkt, MOVTrack *trk)
{
    int length;

    if (pkt->size < 8)
        return;

    length = (AV_RB16(pkt->data) & 0xFFF) * 2;
    if (length < 8 || length > pkt->size)
        return;

    if (AV_RB32(pkt->data + 4) == 0xF8726FBA) {
        trk->cluster[trk->entry].flags |= MOV_SYNC_SAMPLE;
        trk->has_keyframes++;
    }

    return;
}