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
typedef  void* user_tcflag_t ;
typedef  void* user_speed_t ;
struct user_termios {void* c_ospeed; void* c_ispeed; int /*<<< orphan*/  c_cc; void* c_lflag; void* c_cflag; void* c_oflag; void* c_iflag; } ;
struct termios32 {scalar_t__ c_ospeed; scalar_t__ c_ispeed; int /*<<< orphan*/  c_cc; scalar_t__ c_lflag; scalar_t__ c_cflag; scalar_t__ c_oflag; scalar_t__ c_iflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
termios32to64(struct termios32 *in, struct user_termios *out)
{
	out->c_iflag = (user_tcflag_t)in->c_iflag;
	out->c_oflag = (user_tcflag_t)in->c_oflag;
	out->c_cflag = (user_tcflag_t)in->c_cflag;
	out->c_lflag = (user_tcflag_t)in->c_lflag;

	/* bcopy is OK, since this type is ILP32/LP64 size invariant */
	bcopy(in->c_cc, out->c_cc, sizeof(in->c_cc));

	out->c_ispeed = (user_speed_t)in->c_ispeed;
	out->c_ospeed = (user_speed_t)in->c_ospeed;
}