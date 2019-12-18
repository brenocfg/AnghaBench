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
struct dst_node {int dummy; } ;
struct dst_export_ctl {int dummy; } ;
struct dst_ctl {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 struct dst_node* dst_alloc_node (struct dst_ctl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dst_node_add (struct dst_node*) ; 
 int /*<<< orphan*/  dst_node_put (struct dst_node*) ; 
 int dst_setup_export (struct dst_node*,struct dst_ctl*,struct dst_export_ctl*) ; 
 int /*<<< orphan*/  dst_start_export ; 

__attribute__((used)) static int dst_add_export(struct dst_node *n, struct dst_ctl *ctl,
		void *data, unsigned int size)
{
	int err;
	struct dst_export_ctl *le = data;

	if (n)
		return -EEXIST;

	if (size != sizeof(struct dst_export_ctl))
		return -EINVAL;

	n = dst_alloc_node(ctl, dst_start_export, 2);
	if (!n)
		return -EINVAL;

	err = dst_setup_export(n, ctl, le);
	if (err)
		goto err_out_free;

	dst_node_add(n);

	return 0;

err_out_free:
	dst_node_put(n);
	return err;
}