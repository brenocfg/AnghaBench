#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tid_info {unsigned int natids; TYPE_1__* atid_tab; } ;
struct TYPE_2__ {void* data; } ;

/* Variables and functions */

__attribute__((used)) static inline void *lookup_atid(const struct tid_info *t, unsigned int atid)
{
	return atid < t->natids ? t->atid_tab[atid].data : NULL;
}