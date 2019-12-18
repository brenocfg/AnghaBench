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
struct tty_ldisc_ops {int dummy; } ;
struct tty_ldisc {int /*<<< orphan*/  users; struct tty_ldisc_ops* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct tty_ldisc* ERR_CAST (struct tty_ldisc_ops*) ; 
 struct tty_ldisc* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct tty_ldisc_ops*) ; 
 int NR_LDISCS ; 
 int N_TTY ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct tty_ldisc_ops* get_ldops (int) ; 
 struct tty_ldisc* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_ldops (struct tty_ldisc_ops*) ; 
 int /*<<< orphan*/  request_module (char*,int) ; 

__attribute__((used)) static struct tty_ldisc *tty_ldisc_get(int disc)
{
	struct tty_ldisc *ld;
	struct tty_ldisc_ops *ldops;

	if (disc < N_TTY || disc >= NR_LDISCS)
		return ERR_PTR(-EINVAL);

	/*
	 * Get the ldisc ops - we may need to request them to be loaded
	 * dynamically and try again.
	 */
	ldops = get_ldops(disc);
	if (IS_ERR(ldops)) {
		request_module("tty-ldisc-%d", disc);
		ldops = get_ldops(disc);
		if (IS_ERR(ldops))
			return ERR_CAST(ldops);
	}

	ld = kmalloc(sizeof(struct tty_ldisc), GFP_KERNEL);
	if (ld == NULL) {
		put_ldops(ldops);
		return ERR_PTR(-ENOMEM);
	}

	ld->ops = ldops;
	atomic_set(&ld->users, 1);
	return ld;
}