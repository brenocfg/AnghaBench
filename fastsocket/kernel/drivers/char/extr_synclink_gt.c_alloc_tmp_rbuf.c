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
struct slgt_info {int /*<<< orphan*/ * tmp_rbuf; scalar_t__ max_frame_size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_tmp_rbuf(struct slgt_info *info)
{
	info->tmp_rbuf = kmalloc(info->max_frame_size + 5, GFP_KERNEL);
	if (info->tmp_rbuf == NULL)
		return -ENOMEM;
	return 0;
}