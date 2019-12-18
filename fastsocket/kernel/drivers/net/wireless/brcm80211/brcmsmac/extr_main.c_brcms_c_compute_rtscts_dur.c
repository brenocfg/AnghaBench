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
typedef  int u16 ;
struct brcms_c_info {int /*<<< orphan*/  band; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMS_SHORT_PREAMBLE ; 
 scalar_t__ brcms_c_calc_ack_time (struct brcms_c_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ brcms_c_calc_ba_time (struct brcms_c_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ brcms_c_calc_cts_time (struct brcms_c_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ brcms_c_calc_frame_time (struct brcms_c_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_sifs (int /*<<< orphan*/ ) ; 

u16
brcms_c_compute_rtscts_dur(struct brcms_c_info *wlc, bool cts_only,
			   u32 rts_rate,
			   u32 frame_rate, u8 rts_preamble_type,
			   u8 frame_preamble_type, uint frame_len, bool ba)
{
	u16 dur, sifs;

	sifs = get_sifs(wlc->band);

	if (!cts_only) {
		/* RTS/CTS */
		dur = 3 * sifs;
		dur +=
		    (u16) brcms_c_calc_cts_time(wlc, rts_rate,
					       rts_preamble_type);
	} else {
		/* CTS-TO-SELF */
		dur = 2 * sifs;
	}

	dur +=
	    (u16) brcms_c_calc_frame_time(wlc, frame_rate, frame_preamble_type,
					 frame_len);
	if (ba)
		dur +=
		    (u16) brcms_c_calc_ba_time(wlc, frame_rate,
					      BRCMS_SHORT_PREAMBLE);
	else
		dur +=
		    (u16) brcms_c_calc_ack_time(wlc, frame_rate,
					       frame_preamble_type);
	return dur;
}