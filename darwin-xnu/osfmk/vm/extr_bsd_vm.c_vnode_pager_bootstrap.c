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
typedef  int vm_size_t ;
struct vnode_pager {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MAX_VNODE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  Z_CALLERACCT ; 
 int /*<<< orphan*/  Z_NOENCRYPT ; 
 int /*<<< orphan*/  apple_protect_pager_bootstrap () ; 
 int /*<<< orphan*/  fourk_pager_bootstrap () ; 
 int /*<<< orphan*/  shared_region_pager_bootstrap () ; 
 int /*<<< orphan*/  swapfile_pager_bootstrap () ; 
 int /*<<< orphan*/  vnode_pager_zone ; 
 int /*<<< orphan*/  zinit (int,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zone_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
vnode_pager_bootstrap(void)
{
	vm_size_t      size;

	size = (vm_size_t) sizeof(struct vnode_pager);
	vnode_pager_zone = zinit(size, (vm_size_t) MAX_VNODE*size,
				PAGE_SIZE, "vnode pager structures");
	zone_change(vnode_pager_zone, Z_CALLERACCT, FALSE);
	zone_change(vnode_pager_zone, Z_NOENCRYPT, TRUE);


#if CONFIG_CODE_DECRYPTION
	apple_protect_pager_bootstrap();
#endif	/* CONFIG_CODE_DECRYPTION */
	swapfile_pager_bootstrap();
#if __arm64__
	fourk_pager_bootstrap();
#endif /* __arm64__ */
	shared_region_pager_bootstrap();

	return;
}