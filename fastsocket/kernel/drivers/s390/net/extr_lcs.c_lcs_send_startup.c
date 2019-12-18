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
struct TYPE_3__ {int /*<<< orphan*/  buff_size; } ;
struct TYPE_4__ {TYPE_1__ lcs_startup; } ;
struct lcs_cmd {TYPE_2__ cmd; int /*<<< orphan*/  initiator; int /*<<< orphan*/  cmd_code; } ;
struct lcs_card {int dummy; } ;
struct lcs_buffer {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  LCS_CMD_STARTUP ; 
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LCS_IOBUFFERSIZE ; 
 int /*<<< orphan*/  LCS_STD_CMD_SIZE ; 
 struct lcs_buffer* lcs_get_lancmd (struct lcs_card*,int /*<<< orphan*/ ) ; 
 int lcs_send_lancmd (struct lcs_card*,struct lcs_buffer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static int
lcs_send_startup(struct lcs_card *card, __u8 initiator)
{
	struct lcs_buffer *buffer;
	struct lcs_cmd *cmd;

	LCS_DBF_TEXT(2, trace, "startup");
	buffer = lcs_get_lancmd(card, LCS_STD_CMD_SIZE);
	cmd = (struct lcs_cmd *) buffer->data;
	cmd->cmd_code = LCS_CMD_STARTUP;
	cmd->initiator = initiator;
	cmd->cmd.lcs_startup.buff_size = LCS_IOBUFFERSIZE;
	return lcs_send_lancmd(card, buffer, NULL);
}