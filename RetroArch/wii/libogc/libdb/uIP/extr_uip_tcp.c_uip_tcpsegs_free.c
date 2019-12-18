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
struct uip_tcpseg {struct uip_tcpseg* next; } ;

/* Variables and functions */
 scalar_t__ uip_tcpseg_free (struct uip_tcpseg*) ; 

u8_t uip_tcpsegs_free(struct uip_tcpseg *seg)
{
	u8_t cnt = 0;
	struct uip_tcpseg *next;

	while(seg!=NULL) {
		next = seg->next;
		cnt += uip_tcpseg_free(seg);
		seg = next;
	}

	return cnt;
}