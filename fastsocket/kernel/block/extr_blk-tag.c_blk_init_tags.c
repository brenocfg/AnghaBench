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
struct blk_queue_tag {int dummy; } ;

/* Variables and functions */
 struct blk_queue_tag* __blk_queue_init_tags (int /*<<< orphan*/ *,int) ; 

struct blk_queue_tag *blk_init_tags(int depth)
{
	return __blk_queue_init_tags(NULL, depth);
}