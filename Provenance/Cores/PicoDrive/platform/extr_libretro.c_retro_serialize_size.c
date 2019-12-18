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
struct savestate_state {size_t pos; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int PicoStateFP (struct savestate_state*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  state_fseek ; 
 int /*<<< orphan*/  state_skip ; 

size_t retro_serialize_size(void) 
{ 
	struct savestate_state state = { 0, };
	int ret;

	ret = PicoStateFP(&state, 1, NULL, state_skip, NULL, state_fseek);
	if (ret != 0)
		return 0;

	return state.pos;
}