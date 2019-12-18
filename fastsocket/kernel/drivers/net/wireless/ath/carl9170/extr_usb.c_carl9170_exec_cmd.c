#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void u8 ;
struct TYPE_5__ {unsigned int len; int cmd; } ;
struct TYPE_7__ {scalar_t__ data; TYPE_1__ hdr; } ;
struct ar9170 {unsigned int readlen; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/ * readbuf; TYPE_3__ cmd; TYPE_2__* udev; int /*<<< orphan*/  cmd_wait; } ;
typedef  enum carl9170_cmd_oids { ____Placeholder_carl9170_cmd_oids } carl9170_cmd_oids ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int const CARL9170_CMD_ASYNC_FLAG ; 
 int /*<<< orphan*/  CARL9170_RR_COMMAND_TIMEOUT ; 
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int EIO ; 
 int EMSGSIZE ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  IS_ACCEPTING_CMD (struct ar9170*) ; 
 scalar_t__ IS_STARTED (struct ar9170*) ; 
 int __carl9170_exec_cmd (struct ar9170*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  carl9170_restart (struct ar9170*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,unsigned int) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  print_hex_dump_bytes (char*,int /*<<< orphan*/ ,TYPE_3__*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int carl9170_exec_cmd(struct ar9170 *ar, const enum carl9170_cmd_oids cmd,
	unsigned int plen, void *payload, unsigned int outlen, void *out)
{
	int err = -ENOMEM;

	if (!IS_ACCEPTING_CMD(ar))
		return -EIO;

	if (!(cmd & CARL9170_CMD_ASYNC_FLAG))
		might_sleep();

	ar->cmd.hdr.len = plen;
	ar->cmd.hdr.cmd = cmd;
	/* writing multiple regs fills this buffer already */
	if (plen && payload != (u8 *)(ar->cmd.data))
		memcpy(ar->cmd.data, payload, plen);

	spin_lock_bh(&ar->cmd_lock);
	ar->readbuf = (u8 *)out;
	ar->readlen = outlen;
	spin_unlock_bh(&ar->cmd_lock);

	err = __carl9170_exec_cmd(ar, &ar->cmd, false);

	if (!(cmd & CARL9170_CMD_ASYNC_FLAG)) {
		err = wait_for_completion_timeout(&ar->cmd_wait, HZ);
		if (err == 0) {
			err = -ETIMEDOUT;
			goto err_unbuf;
		}

		if (ar->readlen != outlen) {
			err = -EMSGSIZE;
			goto err_unbuf;
		}
	}

	return 0;

err_unbuf:
	/* Maybe the device was removed in the moment we were waiting? */
	if (IS_STARTED(ar)) {
		dev_err(&ar->udev->dev, "no command feedback "
			"received (%d).\n", err);

		/* provide some maybe useful debug information */
		print_hex_dump_bytes("carl9170 cmd: ", DUMP_PREFIX_NONE,
				     &ar->cmd, plen + 4);

		carl9170_restart(ar, CARL9170_RR_COMMAND_TIMEOUT);
	}

	/* invalidate to avoid completing the next command prematurely */
	spin_lock_bh(&ar->cmd_lock);
	ar->readbuf = NULL;
	ar->readlen = 0;
	spin_unlock_bh(&ar->cmd_lock);

	return err;
}