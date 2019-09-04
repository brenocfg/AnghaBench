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
typedef  int u_long ;
struct socket {int dummy; } ;
struct so_cidreq64 {int /*<<< orphan*/  scr_cidp; int /*<<< orphan*/  scr_cnt; int /*<<< orphan*/  scr_aid; } ;
struct so_cidreq32 {int /*<<< orphan*/  scr_cidp; int /*<<< orphan*/  scr_cnt; int /*<<< orphan*/  scr_aid; } ;
typedef  struct so_cidreq64* caddr_t ;

/* Variables and functions */
#define  SIOCGCONNIDS32 129 
#define  SIOCGCONNIDS64 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (struct so_cidreq64*,struct so_cidreq64*,int) ; 
 int in_getconnids (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __attribute__((noinline)) int
inctl_connid(struct socket *so, u_long cmd, caddr_t data)
{
	int error = 0;
	union {
		struct so_cidreq32 c32;
		struct so_cidreq64 c64;
	} u;

	VERIFY(so != NULL);

	switch (cmd) {
	case SIOCGCONNIDS32:		/* struct so_cidreq32 */
		bcopy(data, &u.c32, sizeof (u.c32));
		error = in_getconnids(so, u.c32.scr_aid, &u.c32.scr_cnt,
		    u.c32.scr_cidp);
		if (error == 0)
			bcopy(&u.c32, data, sizeof (u.c32));
		break;

	case SIOCGCONNIDS64:		/* struct so_cidreq64 */
		bcopy(data, &u.c64, sizeof (u.c64));
		error = in_getconnids(so, u.c64.scr_aid, &u.c64.scr_cnt,
		    u.c64.scr_cidp);
		if (error == 0)
			bcopy(&u.c64, data, sizeof (u.c64));
		break;

	default:
		VERIFY(0);
		/* NOTREACHED */
	}

	return (error);
}