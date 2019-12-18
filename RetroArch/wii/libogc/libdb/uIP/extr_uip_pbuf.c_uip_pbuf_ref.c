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
struct uip_pbuf {int /*<<< orphan*/  ref; } ;

/* Variables and functions */

void uip_pbuf_ref(struct uip_pbuf *p)
{
	if(p!=NULL) {
		++(p->ref);
	}
}