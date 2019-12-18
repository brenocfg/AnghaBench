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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct dib8000_state {int timf; int /*<<< orphan*/  timf_default; } ;

/* Variables and functions */
 int dib8000_read32 (struct dib8000_state*,int) ; 
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dib8000_update_timf(struct dib8000_state *state)
{
	u32 timf = state->timf = dib8000_read32(state, 435);

	dib8000_write_word(state, 29, (u16) (timf >> 16));
	dib8000_write_word(state, 30, (u16) (timf & 0xffff));
	dprintk("Updated timing frequency: %d (default: %d)", state->timf, state->timf_default);
}