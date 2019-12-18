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
typedef  int /*<<< orphan*/  uint32_t ;
struct xencons_interface {int in_cons; int in_prod; char* in; } ;
typedef  int XENCONS_RING_IDX ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t MASK_XENCONS_IDX (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  notify_daemon () ; 
 struct xencons_interface* xencons_interface () ; 

__attribute__((used)) static int read_console(uint32_t vtermno, char *buf, int len)
{
	struct xencons_interface *intf = xencons_interface();
	XENCONS_RING_IDX cons, prod;
	int recv = 0;

	cons = intf->in_cons;
	prod = intf->in_prod;
	mb();			/* get pointers before reading ring */
	BUG_ON((prod - cons) > sizeof(intf->in));

	while (cons != prod && recv < len)
		buf[recv++] = intf->in[MASK_XENCONS_IDX(cons++, intf->in)];

	mb();			/* read ring before consuming */
	intf->in_cons = cons;

	notify_daemon();
	return recv;
}