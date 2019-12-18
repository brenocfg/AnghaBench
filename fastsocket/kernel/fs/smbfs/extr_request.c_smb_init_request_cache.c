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
struct smb_request {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int SLAB_HWCACHE_ALIGN ; 
 int SMB_SLAB_DEBUG ; 
 int /*<<< orphan*/ * kmem_cache_create (char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * req_cachep ; 

int smb_init_request_cache(void)
{
	req_cachep = kmem_cache_create("smb_request",
				       sizeof(struct smb_request), 0,
				       SMB_SLAB_DEBUG | SLAB_HWCACHE_ALIGN,
				       NULL);
	if (req_cachep == NULL)
		return -ENOMEM;

	return 0;
}