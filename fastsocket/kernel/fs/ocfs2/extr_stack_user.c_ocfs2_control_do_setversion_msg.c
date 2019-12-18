#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  long u8 ;
struct ocfs2_protocol_version {long pv_major; long pv_minor; } ;
struct TYPE_5__ {long pv_major; long pv_minor; } ;
struct ocfs2_control_private {TYPE_2__ op_proto; } ;
struct ocfs2_control_message_setv {char space1; char space2; char newline; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; int /*<<< orphan*/  tag; } ;
struct file {struct ocfs2_control_private* private_data; } ;
struct TYPE_6__ {TYPE_1__* sp_proto; } ;
struct TYPE_4__ {struct ocfs2_protocol_version lp_max_version; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 long LONG_MAX ; 
 long LONG_MIN ; 
 scalar_t__ OCFS2_CONTROL_HANDSHAKE_PROTOCOL ; 
 int /*<<< orphan*/  OCFS2_CONTROL_MESSAGE_OP_LEN ; 
 int /*<<< orphan*/  OCFS2_CONTROL_MESSAGE_SETVERSION_OP ; 
 scalar_t__ ocfs2_control_get_handshake_state (struct file*) ; 
 int ocfs2_control_install_private (struct file*) ; 
 TYPE_3__ ocfs2_user_plugin ; 
 long simple_strtol (int /*<<< orphan*/ ,char**,int) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_control_do_setversion_msg(struct file *file,
					   struct ocfs2_control_message_setv *msg)
 {
	long major, minor;
	char *ptr = NULL;
	struct ocfs2_control_private *p = file->private_data;
	struct ocfs2_protocol_version *max =
		&ocfs2_user_plugin.sp_proto->lp_max_version;

	if (ocfs2_control_get_handshake_state(file) !=
	    OCFS2_CONTROL_HANDSHAKE_PROTOCOL)
		return -EINVAL;

	if (strncmp(msg->tag, OCFS2_CONTROL_MESSAGE_SETVERSION_OP,
		    OCFS2_CONTROL_MESSAGE_OP_LEN))
		return -EINVAL;

	if ((msg->space1 != ' ') || (msg->space2 != ' ') ||
	    (msg->newline != '\n'))
		return -EINVAL;
	msg->space1 = msg->space2 = msg->newline = '\0';

	major = simple_strtol(msg->major, &ptr, 16);
	if (!ptr || *ptr)
		return -EINVAL;
	minor = simple_strtol(msg->minor, &ptr, 16);
	if (!ptr || *ptr)
		return -EINVAL;

	/*
	 * The major must be between 1 and 255, inclusive.  The minor
	 * must be between 0 and 255, inclusive.  The version passed in
	 * must be within the maximum version supported by the filesystem.
	 */
	if ((major == LONG_MIN) || (major == LONG_MAX) ||
	    (major > (u8)-1) || (major < 1))
		return -ERANGE;
	if ((minor == LONG_MIN) || (minor == LONG_MAX) ||
	    (minor > (u8)-1) || (minor < 0))
		return -ERANGE;
	if ((major != max->pv_major) ||
	    (minor > max->pv_minor))
		return -EINVAL;

	p->op_proto.pv_major = major;
	p->op_proto.pv_minor = minor;

	return ocfs2_control_install_private(file);
}