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
typedef  size_t u16 ;
struct fc_exch_pool {int dummy; } ;
struct fc_exch {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void fc_exch_ptr_set(struct fc_exch_pool *pool, u16 index,
				   struct fc_exch *ep)
{
	((struct fc_exch **)(pool + 1))[index] = ep;
}