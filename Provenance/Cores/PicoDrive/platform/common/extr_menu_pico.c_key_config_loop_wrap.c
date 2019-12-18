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

/* Variables and functions */
#define  MA_CTRL_EMU 130 
#define  MA_CTRL_PLAYER1 129 
#define  MA_CTRL_PLAYER2 128 
 int /*<<< orphan*/  array_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emuctrl_actions ; 
 int /*<<< orphan*/  key_config_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  me_ctrl_actions ; 

__attribute__((used)) static int key_config_loop_wrap(int id, int keys)
{
	switch (id) {
		case MA_CTRL_PLAYER1:
			key_config_loop(me_ctrl_actions, array_size(me_ctrl_actions) - 1, 0);
			break;
		case MA_CTRL_PLAYER2:
			key_config_loop(me_ctrl_actions, array_size(me_ctrl_actions) - 1, 1);
			break;
		case MA_CTRL_EMU:
			key_config_loop(emuctrl_actions, array_size(emuctrl_actions) - 1, -1);
			break;
		default:
			break;
	}
	return 0;
}