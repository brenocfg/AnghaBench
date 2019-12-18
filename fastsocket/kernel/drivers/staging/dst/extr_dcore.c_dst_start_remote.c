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
struct dst_trans {int dummy; } ;
struct dst_node {TYPE_1__* disk; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  first_minor; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_disk (TYPE_1__*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dst_node_create_disk (struct dst_node*) ; 
 int /*<<< orphan*/  dst_node_set_size (struct dst_node*) ; 
 int dst_node_trans_init (struct dst_node*,int) ; 

__attribute__((used)) static int dst_start_remote(struct dst_node *n)
{
	int err;

	err = dst_node_trans_init(n, sizeof(struct dst_trans));
	if (err)
		return err;

	err = dst_node_create_disk(n);
	if (err)
		return err;

	dst_node_set_size(n);
	add_disk(n->disk);

	dprintk("DST: started remote node '%s', minor: %d.\n", n->name, n->disk->first_minor);

	return 0;
}