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
struct tty {int dummy; } ;
struct putchar_args {int flags; struct tty* tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  __doprnt (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct putchar_args*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putchar ; 

int
prf(const char *fmt, va_list ap, int flags, struct tty *ttyp)
{
	struct putchar_args pca;

	pca.flags = flags;
	pca.tty   = ttyp;

	__doprnt(fmt, ap, putchar, &pca, 10, TRUE);

	return 0;
}