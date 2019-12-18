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
typedef  size_t u8 ;
typedef  size_t u16 ;
struct iforce {TYPE_1__* core_effects; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FF_CMD_EFFECT ; 
 int /*<<< orphan*/  FF_CORE_SHOULD_PLAY ; 
 unsigned char HI (size_t) ; 
 unsigned char LO (size_t) ; 
 size_t TIME_SCALE (size_t) ; 
 unsigned char find_button (struct iforce*,size_t) ; 
 int /*<<< orphan*/  iforce_control_playback (struct iforce*,size_t,int) ; 
 int /*<<< orphan*/  iforce_send_packet (struct iforce*,int /*<<< orphan*/ ,unsigned char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int make_core(struct iforce* iforce, u16 id, u16 mod_id1, u16 mod_id2,
	u8 effect_type, u8 axes, u16 duration, u16 delay, u16 button,
	u16 interval, u16 direction)
{
	unsigned char data[14];

	duration = TIME_SCALE(duration);
	delay    = TIME_SCALE(delay);
	interval = TIME_SCALE(interval);

	data[0]  = LO(id);
	data[1]  = effect_type;
	data[2]  = LO(axes) | find_button(iforce, button);

	data[3]  = LO(duration);
	data[4]  = HI(duration);

	data[5]  = HI(direction);

	data[6]  = LO(interval);
	data[7]  = HI(interval);

	data[8]  = LO(mod_id1);
	data[9]  = HI(mod_id1);
	data[10] = LO(mod_id2);
	data[11] = HI(mod_id2);

	data[12] = LO(delay);
	data[13] = HI(delay);

	/* Stop effect */
/*	iforce_control_playback(iforce, id, 0);*/

	iforce_send_packet(iforce, FF_CMD_EFFECT, data);

	/* If needed, restart effect */
	if (test_bit(FF_CORE_SHOULD_PLAY, iforce->core_effects[id].flags)) {
		/* BUG: perhaps we should replay n times, instead of 1. But we do not know n */
		iforce_control_playback(iforce, id, 1);
	}

	return 0;
}