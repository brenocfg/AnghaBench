#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  point; } ;
typedef  TYPE_1__ ccv_mser_node_t ;
struct TYPE_6__ {int reinit; int last_size; int size; int prev_size; int last_mscr_area; int mscr_area; scalar_t__ prev_chi; scalar_t__ chi; scalar_t__ step_now; scalar_t__ rank; int /*<<< orphan*/  max_point; int /*<<< orphan*/  min_point; } ;
typedef  TYPE_2__ ccv_mscr_root_t ;

/* Variables and functions */

__attribute__((used)) static void _ccv_mscr_init_root(ccv_mscr_root_t* root, ccv_mser_node_t* node)
{
	root->reinit = 0x7FFFFFFF;
	root->min_point = root->max_point = node->point;
	root->rank = root->step_now = 0;
	root->chi = root->prev_chi = 0;
	root->last_size = root->size = root->prev_size = 1;
	root->last_mscr_area = root->mscr_area = -1;
}