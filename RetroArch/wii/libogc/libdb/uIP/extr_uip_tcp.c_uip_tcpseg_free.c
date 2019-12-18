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
typedef  int /*<<< orphan*/  u8_t ;
struct uip_tcpseg {int /*<<< orphan*/ * p; } ;

/* Variables and functions */
 int /*<<< orphan*/  memb_free (int /*<<< orphan*/ *,struct uip_tcpseg*) ; 
 int /*<<< orphan*/  uip_pbuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uip_tcp_segs ; 

u8_t uip_tcpseg_free(struct uip_tcpseg *seg)
{
	u8_t cnt = 0;

	if(seg!=NULL) {
		if(seg->p!=NULL) {
			cnt = uip_pbuf_free(seg->p);
		}
		memb_free(&uip_tcp_segs,seg);
	}
	return cnt;
}