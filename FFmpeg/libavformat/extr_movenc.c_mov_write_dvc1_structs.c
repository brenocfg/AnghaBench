#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const uint8_t ;
struct TYPE_6__ {int packet_seq; int packet_entry; int slices; } ;
struct TYPE_9__ {int vos_len; scalar_t__ start_dts; TYPE_3__* st; int /*<<< orphan*/  const* vos_data; TYPE_1__ vc1_info; } ;
struct TYPE_7__ {int num; int den; } ;
struct TYPE_8__ {TYPE_2__ avg_frame_rate; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_4__ MOVTrack ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 scalar_t__ AV_RB32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
 int PROFILE_ADVANCED ; 
 scalar_t__ VC1_CODE_SEQHDR ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  const* av_mallocz (int) ; 
 int /*<<< orphan*/  const* find_next_marker (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_bits32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 
 int vc1_unescape_buffer (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int mov_write_dvc1_structs(MOVTrack *track, uint8_t *buf)
{
    uint8_t *unescaped;
    const uint8_t *start, *next, *end = track->vos_data + track->vos_len;
    int unescaped_size, seq_found = 0;
    int level = 0, interlace = 0;
    int packet_seq   = track->vc1_info.packet_seq;
    int packet_entry = track->vc1_info.packet_entry;
    int slices       = track->vc1_info.slices;
    PutBitContext pbc;

    if (track->start_dts == AV_NOPTS_VALUE) {
        /* No packets written yet, vc1_info isn't authoritative yet. */
        /* Assume inline sequence and entry headers. */
        packet_seq = packet_entry = 1;
        av_log(NULL, AV_LOG_WARNING,
               "moov atom written before any packets, unable to write correct "
               "dvc1 atom. Set the delay_moov flag to fix this.\n");
    }

    unescaped = av_mallocz(track->vos_len + AV_INPUT_BUFFER_PADDING_SIZE);
    if (!unescaped)
        return AVERROR(ENOMEM);
    start = find_next_marker(track->vos_data, end);
    for (next = start; next < end; start = next) {
        GetBitContext gb;
        int size;
        next = find_next_marker(start + 4, end);
        size = next - start - 4;
        if (size <= 0)
            continue;
        unescaped_size = vc1_unescape_buffer(start + 4, size, unescaped);
        init_get_bits(&gb, unescaped, 8 * unescaped_size);
        if (AV_RB32(start) == VC1_CODE_SEQHDR) {
            int profile = get_bits(&gb, 2);
            if (profile != PROFILE_ADVANCED) {
                av_free(unescaped);
                return AVERROR(ENOSYS);
            }
            seq_found = 1;
            level = get_bits(&gb, 3);
            /* chromaformat, frmrtq_postproc, bitrtq_postproc, postprocflag,
             * width, height */
            skip_bits_long(&gb, 2 + 3 + 5 + 1 + 2*12);
            skip_bits(&gb, 1); /* broadcast */
            interlace = get_bits1(&gb);
            skip_bits(&gb, 4); /* tfcntrflag, finterpflag, reserved, psf */
        }
    }
    if (!seq_found) {
        av_free(unescaped);
        return AVERROR(ENOSYS);
    }

    init_put_bits(&pbc, buf, 7);
    /* VC1DecSpecStruc */
    put_bits(&pbc, 4, 12); /* profile - advanced */
    put_bits(&pbc, 3, level);
    put_bits(&pbc, 1, 0); /* reserved */
    /* VC1AdvDecSpecStruc */
    put_bits(&pbc, 3, level);
    put_bits(&pbc, 1, 0); /* cbr */
    put_bits(&pbc, 6, 0); /* reserved */
    put_bits(&pbc, 1, !interlace); /* no interlace */
    put_bits(&pbc, 1, !packet_seq); /* no multiple seq */
    put_bits(&pbc, 1, !packet_entry); /* no multiple entry */
    put_bits(&pbc, 1, !slices); /* no slice code */
    put_bits(&pbc, 1, 0); /* no bframe */
    put_bits(&pbc, 1, 0); /* reserved */

    /* framerate */
    if (track->st->avg_frame_rate.num > 0 && track->st->avg_frame_rate.den > 0)
        put_bits32(&pbc, track->st->avg_frame_rate.num / track->st->avg_frame_rate.den);
    else
        put_bits32(&pbc, 0xffffffff);

    flush_put_bits(&pbc);

    av_free(unescaped);

    return 0;
}