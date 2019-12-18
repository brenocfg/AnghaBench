#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  avctx; } ;
struct TYPE_12__ {int id_aac; int ready_for_dequant; } ;
typedef  TYPE_1__ SpectralBandReplication ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ AACContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int TYPE_CCE ; 
 int TYPE_CPE ; 
 int TYPE_SCE ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 unsigned int get_bits_count (int /*<<< orphan*/ *) ; 
 scalar_t__ read_sbr_channel_pair_element (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_sbr_extension (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int,int*) ; 
 scalar_t__ read_sbr_single_channel_element (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbr_turnoff (TYPE_1__*) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static unsigned int read_sbr_data(AACContext *ac, SpectralBandReplication *sbr,
                                  GetBitContext *gb, int id_aac)
{
    unsigned int cnt = get_bits_count(gb);

    sbr->id_aac = id_aac;
    sbr->ready_for_dequant = 1;

    if (id_aac == TYPE_SCE || id_aac == TYPE_CCE) {
        if (read_sbr_single_channel_element(ac, sbr, gb)) {
            sbr_turnoff(sbr);
            return get_bits_count(gb) - cnt;
        }
    } else if (id_aac == TYPE_CPE) {
        if (read_sbr_channel_pair_element(ac, sbr, gb)) {
            sbr_turnoff(sbr);
            return get_bits_count(gb) - cnt;
        }
    } else {
        av_log(ac->avctx, AV_LOG_ERROR,
            "Invalid bitstream - cannot apply SBR to element type %d\n", id_aac);
        sbr_turnoff(sbr);
        return get_bits_count(gb) - cnt;
    }
    if (get_bits1(gb)) { // bs_extended_data
        int num_bits_left = get_bits(gb, 4); // bs_extension_size
        if (num_bits_left == 15)
            num_bits_left += get_bits(gb, 8); // bs_esc_count

        num_bits_left <<= 3;
        while (num_bits_left > 7) {
            num_bits_left -= 2;
            read_sbr_extension(ac, sbr, gb, get_bits(gb, 2), &num_bits_left); // bs_extension_id
        }
        if (num_bits_left < 0) {
            av_log(ac->avctx, AV_LOG_ERROR, "SBR Extension over read.\n");
        }
        if (num_bits_left > 0)
            skip_bits(gb, num_bits_left);
    }

    return get_bits_count(gb) - cnt;
}