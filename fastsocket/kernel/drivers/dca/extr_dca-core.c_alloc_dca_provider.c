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
struct dca_provider {struct dca_ops* ops; } ;
struct dca_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct dca_provider* kzalloc (int,int /*<<< orphan*/ ) ; 

struct dca_provider *alloc_dca_provider(struct dca_ops *ops, int priv_size)
{
	struct dca_provider *dca;
	int alloc_size;

	alloc_size = (sizeof(*dca) + priv_size);
	dca = kzalloc(alloc_size, GFP_KERNEL);
	if (!dca)
		return NULL;
	dca->ops = ops;

	return dca;
}