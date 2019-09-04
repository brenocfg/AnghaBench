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
struct tty {int dummy; } ;

/* Variables and functions */
 int FNONBLOCK ; 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  TTY_LOCK_OWNED (struct tty*) ; 
 int /*<<< orphan*/  ttyflush (struct tty*,int) ; 
 scalar_t__ ttywflush (struct tty*) ; 

int
ttylclose(struct tty *tp, int flag)
{
	TTY_LOCK_OWNED(tp);	/* debug assert */

	if ( (flag & FNONBLOCK) || ttywflush(tp))
		ttyflush(tp, FREAD | FWRITE);

	return (0);
}