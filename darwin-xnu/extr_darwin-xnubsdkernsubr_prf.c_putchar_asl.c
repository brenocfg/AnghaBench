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
struct putchar_args {int flags; } ;

/* Variables and functions */
 int TOLOGLOCKED ; 
 int /*<<< orphan*/  aslbufp ; 
 int /*<<< orphan*/  log_putc_locked (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  putchar (int,void*) ; 

__attribute__((used)) static void
putchar_asl(int c, void *arg)
{
	struct putchar_args *pca = arg;

	if ((pca->flags & TOLOGLOCKED) && c != '\0' && c != '\r' && c != 0177)
		log_putc_locked(aslbufp, c);
	putchar(c, arg);
}