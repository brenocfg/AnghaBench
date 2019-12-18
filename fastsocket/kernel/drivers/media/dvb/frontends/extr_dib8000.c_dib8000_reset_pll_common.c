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
typedef  int /*<<< orphan*/  u16 ;
struct dibx000_bandwidth_config {int ifreq; int internal; int /*<<< orphan*/  sad_cfg; } ;
struct dib8000_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int,int,int) ; 

__attribute__((used)) static void dib8000_reset_pll_common(struct dib8000_state *state, const struct dibx000_bandwidth_config *bw)
{
	dprintk("ifreq: %d %x, inversion: %d", bw->ifreq, bw->ifreq, bw->ifreq >> 25);
	dib8000_write_word(state, 23, (u16) (((bw->internal * 1000) >> 16) & 0xffff));	/* P_sec_len */
	dib8000_write_word(state, 24, (u16) ((bw->internal * 1000) & 0xffff));
	dib8000_write_word(state, 27, (u16) ((bw->ifreq >> 16) & 0x01ff));
	dib8000_write_word(state, 28, (u16) (bw->ifreq & 0xffff));
	dib8000_write_word(state, 26, (u16) ((bw->ifreq >> 25) & 0x0003));

	dib8000_write_word(state, 922, bw->sad_cfg);
}