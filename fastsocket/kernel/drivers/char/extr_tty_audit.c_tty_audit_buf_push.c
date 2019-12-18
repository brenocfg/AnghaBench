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
typedef  int /*<<< orphan*/  uid_t ;
struct tty_audit_buf {scalar_t__ valid; int /*<<< orphan*/  data; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ audit_enabled ; 
 int /*<<< orphan*/  tty_audit_log (char*,struct task_struct*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void tty_audit_buf_push(struct task_struct *tsk, uid_t loginuid,
			       unsigned int sessionid,
			       struct tty_audit_buf *buf)
{
	if (buf->valid == 0)
		return;
	if (audit_enabled == 0) {
		buf->valid = 0;
		return;
	}
	tty_audit_log("tty", tsk, loginuid, sessionid, buf->major, buf->minor,
		      buf->data, buf->valid);
	buf->valid = 0;
}