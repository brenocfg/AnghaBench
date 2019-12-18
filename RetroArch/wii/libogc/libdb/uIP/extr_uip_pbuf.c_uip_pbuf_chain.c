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
struct uip_pbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  uip_pbuf_cat (struct uip_pbuf*,struct uip_pbuf*) ; 
 int /*<<< orphan*/  uip_pbuf_ref (struct uip_pbuf*) ; 

void uip_pbuf_chain(struct uip_pbuf *h,struct uip_pbuf *t)
{
	uip_pbuf_cat(h,t);
	uip_pbuf_ref(t);
}