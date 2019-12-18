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
struct tty_audit_buf {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_audit_buf_free (struct tty_audit_buf*) ; 

__attribute__((used)) static void tty_audit_buf_put(struct tty_audit_buf *buf)
{
	if (atomic_dec_and_test(&buf->count))
		tty_audit_buf_free(buf);
}