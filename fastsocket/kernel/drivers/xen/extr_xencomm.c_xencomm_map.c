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
struct xencomm_handle {int dummy; } ;
struct xencomm_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int xencomm_create (void*,unsigned long,struct xencomm_desc**,int /*<<< orphan*/ ) ; 
 struct xencomm_handle* xencomm_create_inline (void*) ; 
 scalar_t__ xencomm_is_phys_contiguous (unsigned long) ; 
 struct xencomm_handle* xencomm_pa (struct xencomm_desc*) ; 

struct xencomm_handle *xencomm_map(void *ptr, unsigned long bytes)
{
	int rc;
	struct xencomm_desc *desc;

	if (xencomm_is_phys_contiguous((unsigned long)ptr))
		return xencomm_create_inline(ptr);

	rc = xencomm_create(ptr, bytes, &desc, GFP_KERNEL);

	if (rc || desc == NULL)
		return NULL;

	return xencomm_pa(desc);
}