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
struct scatterlist {int dummy; } ;
struct zfcp_gpn_ft {int /*<<< orphan*/  sg_resp; struct scatterlist sg_req; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpn_ft_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct zfcp_gpn_ft*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_virt (struct scatterlist*) ; 
 TYPE_1__ zfcp_data ; 
 int /*<<< orphan*/  zfcp_sg_free_table (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void zfcp_free_sg_env(struct zfcp_gpn_ft *gpn_ft, int buf_num)
{
	struct scatterlist *sg = &gpn_ft->sg_req;

	kmem_cache_free(zfcp_data.gpn_ft_cache, sg_virt(sg));
	zfcp_sg_free_table(gpn_ft->sg_resp, buf_num);

	kfree(gpn_ft);
}