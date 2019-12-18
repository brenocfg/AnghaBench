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
struct stliport {int /*<<< orphan*/  port; } ;
struct stlibrd {struct stliport** ports; } ;

/* Variables and functions */
 unsigned int STL_MAXPORTS ; 
 int /*<<< orphan*/  kfree (struct stliport*) ; 
 int /*<<< orphan*/  tty_hangup (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stli_cleanup_ports(struct stlibrd *brdp)
{
	struct stliport *portp;
	unsigned int j;
	struct tty_struct *tty;

	for (j = 0; j < STL_MAXPORTS; j++) {
		portp = brdp->ports[j];
		if (portp != NULL) {
			tty = tty_port_tty_get(&portp->port);
			if (tty != NULL) {
				tty_hangup(tty);
				tty_kref_put(tty);
			}
			kfree(portp);
		}
	}
}