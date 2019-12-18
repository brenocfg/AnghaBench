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
struct xencomm_mini {int dummy; } ;
struct xencomm_handle {int dummy; } ;
struct xencomm_desc {int dummy; } ;

/* Variables and functions */
 struct xencomm_handle* xencomm_create_inline (void*) ; 
 int xencomm_create_mini (void*,unsigned long,struct xencomm_mini*,struct xencomm_desc**) ; 
 scalar_t__ xencomm_is_phys_contiguous (unsigned long) ; 
 struct xencomm_handle* xencomm_pa (struct xencomm_desc*) ; 

struct xencomm_handle *__xencomm_map_no_alloc(void *ptr, unsigned long bytes,
			struct xencomm_mini *xc_desc)
{
	int rc;
	struct xencomm_desc *desc = NULL;

	if (xencomm_is_phys_contiguous((unsigned long)ptr))
		return xencomm_create_inline(ptr);

	rc = xencomm_create_mini(ptr, bytes, xc_desc,
				&desc);

	if (rc)
		return NULL;

	return xencomm_pa(desc);
}