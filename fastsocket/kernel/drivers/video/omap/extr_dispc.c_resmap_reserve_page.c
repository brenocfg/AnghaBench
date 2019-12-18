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
struct resmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESMAP_MASK (unsigned int) ; 
 int /*<<< orphan*/ * RESMAP_PTR (struct resmap*,unsigned int) ; 
 int /*<<< orphan*/  resmap_page_reserved (struct resmap*,unsigned int) ; 

__attribute__((used)) static inline void resmap_reserve_page(struct resmap *res_map, unsigned page_nr)
{
	BUG_ON(resmap_page_reserved(res_map, page_nr));
	*RESMAP_PTR(res_map, page_nr) |= RESMAP_MASK(page_nr);
}