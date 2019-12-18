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
struct ocfs2_control_private {long op_this_node; } ;
struct ocfs2_control_message_setn {char space; char newline; int /*<<< orphan*/  nodestr; int /*<<< orphan*/  tag; } ;
struct file {struct ocfs2_control_private* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 long INT_MAX ; 
 long LONG_MAX ; 
 long LONG_MIN ; 
 scalar_t__ OCFS2_CONTROL_HANDSHAKE_PROTOCOL ; 
 int /*<<< orphan*/  OCFS2_CONTROL_MESSAGE_OP_LEN ; 
 int /*<<< orphan*/  OCFS2_CONTROL_MESSAGE_SETNODE_OP ; 
 scalar_t__ ocfs2_control_get_handshake_state (struct file*) ; 
 int ocfs2_control_install_private (struct file*) ; 
 long simple_strtol (int /*<<< orphan*/ ,char**,int) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_control_do_setnode_msg(struct file *file,
					struct ocfs2_control_message_setn *msg)
{
	long nodenum;
	char *ptr = NULL;
	struct ocfs2_control_private *p = file->private_data;

	if (ocfs2_control_get_handshake_state(file) !=
	    OCFS2_CONTROL_HANDSHAKE_PROTOCOL)
		return -EINVAL;

	if (strncmp(msg->tag, OCFS2_CONTROL_MESSAGE_SETNODE_OP,
		    OCFS2_CONTROL_MESSAGE_OP_LEN))
		return -EINVAL;

	if ((msg->space != ' ') || (msg->newline != '\n'))
		return -EINVAL;
	msg->space = msg->newline = '\0';

	nodenum = simple_strtol(msg->nodestr, &ptr, 16);
	if (!ptr || *ptr)
		return -EINVAL;

	if ((nodenum == LONG_MIN) || (nodenum == LONG_MAX) ||
	    (nodenum > INT_MAX) || (nodenum < 0))
		return -ERANGE;
	p->op_this_node = nodenum;

	return ocfs2_control_install_private(file);
}