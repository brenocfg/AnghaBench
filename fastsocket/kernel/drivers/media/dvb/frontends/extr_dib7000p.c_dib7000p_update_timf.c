#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {TYPE_1__* bw; } ;
struct dib7000p_state {int timf; int current_bandwidth; TYPE_2__ cfg; } ;
struct TYPE_3__ {int /*<<< orphan*/  timf; } ;

/* Variables and functions */
 int dib7000p_read_word (struct dib7000p_state*,int) ; 
 int /*<<< orphan*/  dib7000p_write_word (struct dib7000p_state*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dib7000p_update_timf(struct dib7000p_state *state)
{
	u32 timf = (dib7000p_read_word(state, 427) << 16) | dib7000p_read_word(state, 428);
	state->timf = timf * 160 / (state->current_bandwidth / 50);
	dib7000p_write_word(state, 23, (u16) (timf >> 16));
	dib7000p_write_word(state, 24, (u16) (timf & 0xffff));
	dprintk( "updated timf_frequency: %d (default: %d)",state->timf, state->cfg.bw->timf);

}