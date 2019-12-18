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
struct poseidon {int state; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int ENODEV ; 
 int ENXIO ; 
 int POSEIDON_STATE_DISCONNECT ; 
 int /*<<< orphan*/  TUNE_MODE_SELECT ; 
 scalar_t__ send_set_req (struct poseidon*,int /*<<< orphan*/ ,unsigned char,scalar_t__*) ; 

int set_tuner_mode(struct poseidon *pd, unsigned char mode)
{
	s32 ret, cmd_status;

	if (pd->state & POSEIDON_STATE_DISCONNECT)
		return -ENODEV;

	ret = send_set_req(pd, TUNE_MODE_SELECT, mode, &cmd_status);
	if (ret || cmd_status)
		return -ENXIO;
	return 0;
}