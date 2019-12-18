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
struct tty_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_write ; 
 int /*<<< orphan*/  __simc (int /*<<< orphan*/ ,int,unsigned long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rs_put_char(struct tty_struct *tty, unsigned char ch)
{
	char buf[2];

	buf[0] = ch;
	buf[1] = '\0';		/* Is this NULL necessary? */
	__simc (SYS_write, 1, (unsigned long) buf, 1, 0, 0);
	return 1;
}