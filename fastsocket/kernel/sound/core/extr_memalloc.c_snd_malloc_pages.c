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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __GFP_COMP ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int) ; 
 int get_order (size_t) ; 
 int /*<<< orphan*/  inc_snd_pages (int) ; 

void *snd_malloc_pages(size_t size, gfp_t gfp_flags)
{
	int pg;
	void *res;

	if (WARN_ON(!size))
		return NULL;
	if (WARN_ON(!gfp_flags))
		return NULL;
	gfp_flags |= __GFP_COMP;	/* compound page lets parts be mapped */
	pg = get_order(size);
	if ((res = (void *) __get_free_pages(gfp_flags, pg)) != NULL)
		inc_snd_pages(pg);
	return res;
}