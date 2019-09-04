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
struct pager_crypt_info {scalar_t__ crypt_refcnt; int /*<<< orphan*/  (* crypt_end ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  crypt_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAddAtomic (int,scalar_t__*) ; 
 int /*<<< orphan*/  kfree (struct pager_crypt_info*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void
crypt_info_deallocate(
	struct pager_crypt_info	*crypt_info)
{
#if CRYPT_INFO_DEBUG
	printf("CRYPT_INFO %s: %p ref %d -> %d\n",
	       __FUNCTION__,
	       crypt_info,
	       crypt_info->crypt_refcnt,
	       crypt_info->crypt_refcnt - 1);
#endif /* CRYPT_INFO_DEBUG */
	OSAddAtomic(-1, &crypt_info->crypt_refcnt);
	if (crypt_info->crypt_refcnt == 0) {
		/* deallocate any crypt module data */
		if (crypt_info->crypt_end) {
			crypt_info->crypt_end(crypt_info->crypt_ops);
			crypt_info->crypt_end = NULL;
		}
#if CRYPT_INFO_DEBUG
		printf("CRYPT_INFO %s: freeing %p\n",
		       __FUNCTION__,
		       crypt_info);
#endif /* CRYPT_INFO_DEBUG */
		kfree(crypt_info, sizeof (*crypt_info));
		crypt_info = NULL;
	}
}