#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct brcms_c_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ DOT11_BA_BITMAP_LEN ; 
 scalar_t__ DOT11_BA_LEN ; 
 scalar_t__ FCS_LEN ; 
 int /*<<< orphan*/  brcms_basic_rate (struct brcms_c_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_calc_frame_time (struct brcms_c_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static uint
brcms_c_calc_ba_time(struct brcms_c_info *wlc, u32 rspec,
		     u8 preamble_type)
{
	/*
	 * Spec 9.6: ack rate is the highest rate in BSSBasicRateSet that
	 * is less than or equal to the rate of the immediately previous
	 * frame in the FES
	 */
	rspec = brcms_basic_rate(wlc, rspec);
	/* BA len == 32 == 16(ctl hdr) + 4(ba len) + 8(bitmap) + 4(fcs) */
	return brcms_c_calc_frame_time(wlc, rspec, preamble_type,
				   (DOT11_BA_LEN + DOT11_BA_BITMAP_LEN +
				    FCS_LEN));
}