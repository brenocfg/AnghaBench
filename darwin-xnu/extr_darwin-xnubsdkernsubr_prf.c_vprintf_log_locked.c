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
typedef  int /*<<< orphan*/  va_list ;
struct putchar_args {int /*<<< orphan*/ * tty; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TOLOGLOCKED ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  __doprnt (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct putchar_args*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putchar ; 

int
vprintf_log_locked(const char *fmt, va_list ap)
{
	struct putchar_args pca;

	pca.flags = TOLOGLOCKED;
	pca.tty   = NULL;
	__doprnt(fmt, ap, putchar, &pca, 10, TRUE);
	return 0;
}