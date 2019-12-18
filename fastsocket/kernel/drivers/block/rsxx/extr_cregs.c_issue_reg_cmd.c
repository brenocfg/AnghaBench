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
struct rsxx_reg_access {int /*<<< orphan*/  stat; int /*<<< orphan*/  stream; int /*<<< orphan*/  data; int /*<<< orphan*/  cnt; int /*<<< orphan*/  addr; } ;
struct rsxx_cardinfo {int dummy; } ;

/* Variables and functions */
 unsigned int CREG_OP_READ ; 
 unsigned int CREG_OP_WRITE ; 
 int __issue_creg_rw (struct rsxx_cardinfo*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int issue_reg_cmd(struct rsxx_cardinfo *card,
			 struct rsxx_reg_access *cmd,
			 int read)
{
	unsigned int op = read ? CREG_OP_READ : CREG_OP_WRITE;

	return __issue_creg_rw(card, op, cmd->addr, cmd->cnt, cmd->data,
			       cmd->stream, &cmd->stat);
}