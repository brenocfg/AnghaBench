#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const uint8_t ;
struct TYPE_10__ {int size; int flags; int /*<<< orphan*/  const* data; } ;
struct TYPE_7__ {int slices; int first_packet_seen; int first_frag_written; int first_packet_seq; int first_packet_entry; int packet_seq; int packet_entry; } ;
struct TYPE_9__ {int entry; int has_keyframes; TYPE_2__* cluster; TYPE_1__ vc1_info; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ MOVTrack ;
typedef  TYPE_4__ AVPacket ;

/* Variables and functions */
 int AV_PKT_FLAG_KEY ; 
 int AV_RB32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  MOV_SYNC_SAMPLE ; 
#define  VC1_CODE_ENTRYPOINT 130 
#define  VC1_CODE_SEQHDR 129 
#define  VC1_CODE_SLICE 128 
 int /*<<< orphan*/  const* find_next_marker (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void mov_parse_vc1_frame(AVPacket *pkt, MOVTrack *trk)
{
    const uint8_t *start, *next, *end = pkt->data + pkt->size;
    int seq = 0, entry = 0;
    int key = pkt->flags & AV_PKT_FLAG_KEY;
    start = find_next_marker(pkt->data, end);
    for (next = start; next < end; start = next) {
        next = find_next_marker(start + 4, end);
        switch (AV_RB32(start)) {
        case VC1_CODE_SEQHDR:
            seq = 1;
            break;
        case VC1_CODE_ENTRYPOINT:
            entry = 1;
            break;
        case VC1_CODE_SLICE:
            trk->vc1_info.slices = 1;
            break;
        }
    }
    if (!trk->entry && trk->vc1_info.first_packet_seen)
        trk->vc1_info.first_frag_written = 1;
    if (!trk->entry && !trk->vc1_info.first_frag_written) {
        /* First packet in first fragment */
        trk->vc1_info.first_packet_seq   = seq;
        trk->vc1_info.first_packet_entry = entry;
        trk->vc1_info.first_packet_seen  = 1;
    } else if ((seq && !trk->vc1_info.packet_seq) ||
               (entry && !trk->vc1_info.packet_entry)) {
        int i;
        for (i = 0; i < trk->entry; i++)
            trk->cluster[i].flags &= ~MOV_SYNC_SAMPLE;
        trk->has_keyframes = 0;
        if (seq)
            trk->vc1_info.packet_seq = 1;
        if (entry)
            trk->vc1_info.packet_entry = 1;
        if (!trk->vc1_info.first_frag_written) {
            /* First fragment */
            if ((!seq   || trk->vc1_info.first_packet_seq) &&
                (!entry || trk->vc1_info.first_packet_entry)) {
                /* First packet had the same headers as this one, readd the
                 * sync sample flag. */
                trk->cluster[0].flags |= MOV_SYNC_SAMPLE;
                trk->has_keyframes = 1;
            }
        }
    }
    if (trk->vc1_info.packet_seq && trk->vc1_info.packet_entry)
        key = seq && entry;
    else if (trk->vc1_info.packet_seq)
        key = seq;
    else if (trk->vc1_info.packet_entry)
        key = entry;
    if (key) {
        trk->cluster[trk->entry].flags |= MOV_SYNC_SAMPLE;
        trk->has_keyframes++;
    }
}