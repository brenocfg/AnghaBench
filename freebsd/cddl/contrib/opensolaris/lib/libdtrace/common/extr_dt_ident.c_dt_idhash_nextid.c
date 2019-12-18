#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
struct TYPE_3__ {scalar_t__ dh_nextid; scalar_t__ dh_maxid; } ;
typedef  TYPE_1__ dt_idhash_t ;

/* Variables and functions */

int
dt_idhash_nextid(dt_idhash_t *dhp, uint_t *p)
{
	if (dhp->dh_nextid >= dhp->dh_maxid)
		return (-1); /* no more id's are free to allocate */

	*p = dhp->dh_nextid++;
	return (0);
}