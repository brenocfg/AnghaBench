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
struct vcc_state {int family; } ;
struct seq_operations {int dummy; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct vcc_state* __seq_open_private (struct file*,struct seq_operations const*,int) ; 

__attribute__((used)) static int __vcc_seq_open(struct inode *inode, struct file *file,
	int family, const struct seq_operations *ops)
{
	struct vcc_state *state;

	state = __seq_open_private(file, ops, sizeof(*state));
	if (state == NULL)
		return -ENOMEM;

	state->family = family;
	return 0;
}