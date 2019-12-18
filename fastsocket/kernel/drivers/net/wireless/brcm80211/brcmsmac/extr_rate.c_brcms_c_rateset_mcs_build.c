#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct brcms_c_rateset {int /*<<< orphan*/ * mcs; } ;
struct TYPE_2__ {int /*<<< orphan*/ * mcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCSSET_LEN ; 
 int /*<<< orphan*/  brcms_c_rateset_mcs_upd (struct brcms_c_rateset*,int /*<<< orphan*/ ) ; 
 TYPE_1__ cck_ofdm_mimo_rates ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void brcms_c_rateset_mcs_build(struct brcms_c_rateset *rateset, u8 txstreams)
{
	memcpy(&rateset->mcs[0], &cck_ofdm_mimo_rates.mcs[0], MCSSET_LEN);
	brcms_c_rateset_mcs_upd(rateset, txstreams);
}