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
typedef  int /*<<< orphan*/  zone_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  getbufzone (int) ; 
 int /*<<< orphan*/  recycle_buf_failed ; 
 void* recycle_buf_from_pool (int) ; 
 scalar_t__ set_vm_privilege (scalar_t__) ; 
 void* zalloc (int /*<<< orphan*/ ) ; 
 void* zalloc_nopagewait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zalloc_nopagewait_failed ; 

__attribute__((used)) static void *
grab_memory_for_meta_buf(int nsize)
{
	zone_t z;
	void *ptr;
	boolean_t was_vmpriv;

	z = getbufzone(nsize);

	/*
	 * make sure we're NOT priviliged so that
	 * if a vm_page_grab is needed, it won't
	 * block if we're out of free pages... if
	 * it blocks, then we can't honor the
	 * nopagewait request
	 */
	was_vmpriv = set_vm_privilege(FALSE);

	ptr = zalloc_nopagewait(z);

	if (was_vmpriv == TRUE)
		set_vm_privilege(TRUE);

	if (ptr == NULL) {

		zalloc_nopagewait_failed++;

		ptr = recycle_buf_from_pool(nsize);

		if (ptr == NULL) {

			recycle_buf_failed++;

			if (was_vmpriv == FALSE)
				set_vm_privilege(TRUE);

			ptr = zalloc(z);

			if (was_vmpriv == FALSE)
				set_vm_privilege(FALSE);
		}
	}
	return (ptr);
}