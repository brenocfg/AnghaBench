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
typedef  int u8 ;
struct dib0070_state {int* wbd_offset_3_3; } ;

/* Variables and functions */
 int dib0070_read_wbd_offset (struct dib0070_state*,int) ; 
 int /*<<< orphan*/  dprintk (char*,int,int) ; 

__attribute__((used)) static void dib0070_wbd_offset_calibration(struct dib0070_state *state)
{
    u8 gain;
    for (gain = 6; gain < 8; gain++) {
	state->wbd_offset_3_3[gain - 6] = ((dib0070_read_wbd_offset(state, gain) * 8 * 18 / 33 + 1) / 2);
	dprintk("Gain: %d, WBDOffset (3.3V) = %hd", gain, state->wbd_offset_3_3[gain-6]);
    }
}