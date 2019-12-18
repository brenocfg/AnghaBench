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
struct tid_info {unsigned int ntids; struct t3c_tid_entry* tid_tab; } ;
struct t3c_tid_entry {scalar_t__ client; } ;

/* Variables and functions */

__attribute__((used)) static inline struct t3c_tid_entry *lookup_tid(const struct tid_info *t,
					       unsigned int tid)
{
	struct t3c_tid_entry *t3c_tid = tid < t->ntids ?
	    &(t->tid_tab[tid]) : NULL;

	return (t3c_tid && t3c_tid->client) ? t3c_tid : NULL;
}