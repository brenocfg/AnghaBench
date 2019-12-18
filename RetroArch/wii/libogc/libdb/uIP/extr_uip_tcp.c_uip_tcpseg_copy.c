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
struct uip_tcpseg {int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIP_MEMCPY (struct uip_tcpseg*,struct uip_tcpseg*,int) ; 
 struct uip_tcpseg* memb_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uip_pbuf_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uip_tcp_segs ; 

struct uip_tcpseg* uip_tcpseg_copy(struct uip_tcpseg *seg)
{
	struct uip_tcpseg *cseg;

	cseg = memb_alloc(&uip_tcp_segs);
	if(cseg==NULL) return NULL;

	UIP_MEMCPY(cseg,seg,sizeof(struct uip_tcpseg));
	uip_pbuf_ref(cseg->p);

	return cseg;
}