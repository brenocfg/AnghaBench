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
struct tty_audit_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  audit_get_loginuid (int /*<<< orphan*/ ) ; 
 unsigned int audit_get_sessionid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  tty_audit_buf_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,struct tty_audit_buf*) ; 

__attribute__((used)) static void tty_audit_buf_push_current(struct tty_audit_buf *buf)
{
	uid_t auid = audit_get_loginuid(current);
	unsigned int sessionid = audit_get_sessionid(current);
	tty_audit_buf_push(current, auid, sessionid, buf);
}