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
struct pager_crypt_info {scalar_t__ crypt_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAddAtomic (int,scalar_t__*) ; 
 int /*<<< orphan*/  assert (int) ; 

void
crypt_info_reference(
	struct pager_crypt_info *crypt_info)
{
	assert(crypt_info->crypt_refcnt != 0);
#if CRYPT_INFO_DEBUG
	printf("CRYPT_INFO %s: %p ref %d -> %d\n",
	       __FUNCTION__,
	       crypt_info,
	       crypt_info->crypt_refcnt,
	       crypt_info->crypt_refcnt + 1);
#endif /* CRYPT_INFO_DEBUG */
	OSAddAtomic(+1, &crypt_info->crypt_refcnt);
}