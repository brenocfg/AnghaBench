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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct uwb_rceb {int dummy; } ;
struct uwb_rccb {int /*<<< orphan*/  bCommandContext; } ;
struct uwb_rc_cmd_done_params {size_t reply_size; struct uwb_rceb* reply; int /*<<< orphan*/  completion; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;
struct uwb_rc {TYPE_1__ uwb_dev; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 size_t uwb_rc_cmd_async (struct uwb_rc*,char const*,struct uwb_rccb*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uwb_rc_cmd_done_params*) ; 
 int /*<<< orphan*/  uwb_rc_cmd_done ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
ssize_t __uwb_rc_cmd(struct uwb_rc *rc, const char *cmd_name,
		     struct uwb_rccb *cmd, size_t cmd_size,
		     struct uwb_rceb *reply, size_t reply_size,
		     u8 expected_type, u16 expected_event,
		     struct uwb_rceb **preply)
{
	ssize_t result = 0;
	struct device *dev = &rc->uwb_dev.dev;
	struct uwb_rc_cmd_done_params params;

	init_completion(&params.completion);
	params.reply = reply;
	params.reply_size = reply_size;

	result = uwb_rc_cmd_async(rc, cmd_name, cmd, cmd_size,
				  expected_type, expected_event,
				  uwb_rc_cmd_done, &params);
	if (result)
		return result;

	wait_for_completion(&params.completion);

	if (preply)
		*preply = params.reply;

	if (params.reply_size < 0)
		dev_err(dev, "%s: confirmation event 0x%02x/%04x/%02x "
			"reception failed: %d\n", cmd_name,
			expected_type, expected_event, cmd->bCommandContext,
			(int)params.reply_size);
	return params.reply_size;
}