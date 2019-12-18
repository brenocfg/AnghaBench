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
struct audpp_cmd_routing_mode {int /*<<< orphan*/  routing_mode; int /*<<< orphan*/  object_number; int /*<<< orphan*/  cmd_id; } ;
struct audio {scalar_t__ pcm_feedback; int /*<<< orphan*/  dec_id; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  AUDPP_CMD_ROUTING_MODE ; 
 int /*<<< orphan*/  ROUTING_MODE_FTRT ; 
 int /*<<< orphan*/  ROUTING_MODE_RT ; 
 int /*<<< orphan*/  audpp_send_queue1 (struct audpp_cmd_routing_mode*,int) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  memset (struct audpp_cmd_routing_mode*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void audpp_cmd_cfg_routing_mode(struct audio *audio)
{
	struct audpp_cmd_routing_mode cmd;
	dprintk("audpp_cmd_cfg_routing_mode()\n");
	memset(&cmd, 0, sizeof(cmd));
	cmd.cmd_id = AUDPP_CMD_ROUTING_MODE;
	cmd.object_number = audio->dec_id;
	if (audio->pcm_feedback)
		cmd.routing_mode = ROUTING_MODE_FTRT;
	else
		cmd.routing_mode = ROUTING_MODE_RT;
	audpp_send_queue1(&cmd, sizeof(cmd));
}