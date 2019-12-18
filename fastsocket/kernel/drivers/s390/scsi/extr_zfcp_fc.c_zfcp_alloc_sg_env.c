#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct zfcp_gpn_ft {int /*<<< orphan*/  sg_resp; int /*<<< orphan*/  sg_req; } ;
struct ct_iu_gpn_ft_req {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpn_ft_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct zfcp_gpn_ft*) ; 
 struct ct_iu_gpn_ft_req* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct zfcp_gpn_ft* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_one (int /*<<< orphan*/ *,struct ct_iu_gpn_ft_req*,int) ; 
 TYPE_1__ zfcp_data ; 
 int /*<<< orphan*/  zfcp_free_sg_env (struct zfcp_gpn_ft*,int) ; 
 scalar_t__ zfcp_sg_setup_table (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct zfcp_gpn_ft *zfcp_alloc_sg_env(int buf_num)
{
	struct zfcp_gpn_ft *gpn_ft;
	struct ct_iu_gpn_ft_req *req;

	gpn_ft = kzalloc(sizeof(*gpn_ft), GFP_KERNEL);
	if (!gpn_ft)
		return NULL;

	req = kmem_cache_zalloc(zfcp_data.gpn_ft_cache, GFP_KERNEL);
	if (!req) {
		kfree(gpn_ft);
		gpn_ft = NULL;
		goto out;
	}
	sg_init_one(&gpn_ft->sg_req, req, sizeof(*req));

	if (zfcp_sg_setup_table(gpn_ft->sg_resp, buf_num)) {
		zfcp_free_sg_env(gpn_ft, buf_num);
		gpn_ft = NULL;
	}
out:
	return gpn_ft;
}