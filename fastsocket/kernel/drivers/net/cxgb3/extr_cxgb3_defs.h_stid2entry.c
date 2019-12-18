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
typedef  union listen_entry {int dummy; } listen_entry ;
struct tid_info {unsigned int stid_base; union listen_entry* stid_tab; } ;

/* Variables and functions */

__attribute__((used)) static inline union listen_entry *stid2entry(const struct tid_info *t,
					     unsigned int stid)
{
	return &t->stid_tab[stid - t->stid_base];
}