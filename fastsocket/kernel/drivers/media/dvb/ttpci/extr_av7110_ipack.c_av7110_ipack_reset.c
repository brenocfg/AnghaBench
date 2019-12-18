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
struct ipack {scalar_t__ count; scalar_t__ done; scalar_t__ which; scalar_t__ check; scalar_t__ mpeg; scalar_t__ hlength; scalar_t__ flag2; scalar_t__ flag1; scalar_t__ plength; scalar_t__ cid; scalar_t__ found; } ;

/* Variables and functions */

void av7110_ipack_reset(struct ipack *p)
{
	p->found = 0;
	p->cid = 0;
	p->plength = 0;
	p->flag1 = 0;
	p->flag2 = 0;
	p->hlength = 0;
	p->mpeg = 0;
	p->check = 0;
	p->which = 0;
	p->done = 0;
	p->count = 0;
}