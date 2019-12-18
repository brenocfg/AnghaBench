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
 int RESMAP_MASK (unsigned int) ; 
 int* RESMAP_PTR (struct resmap*,unsigned int) ; 

__attribute__((used)) static inline int resmap_page_reserved(struct resmap *res_map, unsigned page_nr)
{
	return *RESMAP_PTR(res_map, page_nr) & RESMAP_MASK(page_nr) ? 1 : 0;
}