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
typedef  size_t uint32_t ;
struct adsp_info {int send_irq; int read_ctrl; int write_ctrl; int max_msg16_size; int max_msg32_size; int max_task_id; int max_image_id; int /*<<< orphan*/  module; int /*<<< orphan*/  module_count; int /*<<< orphan*/ ** task_to_module; int /*<<< orphan*/ ** queue_offset; int /*<<< orphan*/  max_queue_id; scalar_t__ max_module_id; TYPE_1__* init_info_ptr; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** task_to_module_tbl; int /*<<< orphan*/ ** queue_offsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 size_t IMG_MAX ; 
 int /*<<< orphan*/  QDSP_MAX_NUM_QUEUES ; 
 scalar_t__ QDSP_MODULE_MAX ; 
 int /*<<< orphan*/  module_info ; 
 int /*<<< orphan*/ ** qdsp_queue_offset_table ; 
 int /*<<< orphan*/ ** qdsp_task_to_module ; 

int adsp_init_info(struct adsp_info *info)
{
	uint32_t img_num;

	info->send_irq =   0x00c00200;
	info->read_ctrl =  0x00400038;
	info->write_ctrl = 0x00400034;

	info->max_msg16_size = 193;
	info->max_msg32_size = 8;
	for (img_num = 0; img_num < IMG_MAX; img_num++)
		qdsp_queue_offset_table[img_num] =
		&info->init_info_ptr->queue_offsets[img_num][0];

	for (img_num = 0; img_num < IMG_MAX; img_num++)
		qdsp_task_to_module[img_num] =
		&info->init_info_ptr->task_to_module_tbl[img_num][0];
	info->max_task_id = 30;
	info->max_module_id = QDSP_MODULE_MAX - 1;
	info->max_queue_id = QDSP_MAX_NUM_QUEUES;
	info->max_image_id = 2;
	info->queue_offset = qdsp_queue_offset_table;
	info->task_to_module = qdsp_task_to_module;

	info->module_count = ARRAY_SIZE(module_info);
	info->module = module_info;
	return 0;
}