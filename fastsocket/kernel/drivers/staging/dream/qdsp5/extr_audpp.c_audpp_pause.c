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
typedef  int u16 ;
typedef  int /*<<< orphan*/  pause_cmd ;

/* Variables and functions */
 int AUDPP_CMD_DEC_CTRL ; 
 int AUDPP_CMD_DEC_CTRL_LEN ; 
 int AUDPP_CMD_PAUSE_V ; 
 int AUDPP_CMD_RESUME_V ; 
 int AUDPP_CMD_UPDATE_V ; 
 unsigned int CH_COUNT ; 
 int EINVAL ; 
 int audpp_send_queue1 (int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

int audpp_pause(unsigned id, int pause)
{
	/* pause 1 = pause 0 = resume */
	u16 pause_cmd[AUDPP_CMD_DEC_CTRL_LEN / sizeof(unsigned short)];

	if (id >= CH_COUNT)
		return -EINVAL;

	memset(pause_cmd, 0, sizeof(pause_cmd));

	pause_cmd[0] = AUDPP_CMD_DEC_CTRL;
	if (pause == 1)
		pause_cmd[1 + id] = AUDPP_CMD_UPDATE_V | AUDPP_CMD_PAUSE_V;
	else if (pause == 0)
		pause_cmd[1 + id] = AUDPP_CMD_UPDATE_V | AUDPP_CMD_RESUME_V;
	else
		return -EINVAL;

	return audpp_send_queue1(pause_cmd, sizeof(pause_cmd));
}