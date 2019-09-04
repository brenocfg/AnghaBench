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
 int /*<<< orphan*/  FREAD ; 
 int /*<<< orphan*/  TTY_LOCK_OWNED (struct tty*) ; 
 int /*<<< orphan*/  ttyflush (struct tty*,int /*<<< orphan*/ ) ; 
 int ttywait (struct tty*) ; 

__attribute__((used)) static int
ttywflush(struct tty *tp)
{
	int error;

	TTY_LOCK_OWNED(tp);	/* debug assert */

	if ((error = ttywait(tp)) == 0)
		ttyflush(tp, FREAD);
	return (error);
}