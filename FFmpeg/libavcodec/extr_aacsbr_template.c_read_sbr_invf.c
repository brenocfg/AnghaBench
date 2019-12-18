#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/ ** bs_invf_mode; } ;
struct TYPE_5__ {int n_q; } ;
typedef  TYPE_1__ SpectralBandReplication ;
typedef  TYPE_2__ SBRData ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void read_sbr_invf(SpectralBandReplication *sbr, GetBitContext *gb,
                          SBRData *ch_data)
{
    int i;

    memcpy(ch_data->bs_invf_mode[1], ch_data->bs_invf_mode[0], 5 * sizeof(uint8_t));
    for (i = 0; i < sbr->n_q; i++)
        ch_data->bs_invf_mode[0][i] = get_bits(gb, 2);
}