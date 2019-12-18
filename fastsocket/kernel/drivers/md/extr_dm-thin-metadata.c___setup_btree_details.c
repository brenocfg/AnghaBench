#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int size; int /*<<< orphan*/ * equal; int /*<<< orphan*/ * dec; int /*<<< orphan*/ * inc; int /*<<< orphan*/ * context; } ;
struct TYPE_16__ {int levels; TYPE_6__ value_type; int /*<<< orphan*/  tm; } ;
struct TYPE_13__ {int size; void* equal; void* dec; void* inc; int /*<<< orphan*/  context; } ;
struct TYPE_14__ {int levels; TYPE_4__ value_type; int /*<<< orphan*/  tm; } ;
struct TYPE_11__ {int size; int /*<<< orphan*/  equal; int /*<<< orphan*/  dec; int /*<<< orphan*/  inc; TYPE_5__* context; } ;
struct TYPE_12__ {int levels; TYPE_2__ value_type; int /*<<< orphan*/  tm; } ;
struct TYPE_17__ {int /*<<< orphan*/  tm; } ;
struct TYPE_10__ {int size; void* equal; void* dec; void* inc; int /*<<< orphan*/  context; } ;
struct TYPE_18__ {int levels; TYPE_1__ value_type; int /*<<< orphan*/  tm; } ;
struct dm_pool_metadata {TYPE_7__ details_info; int /*<<< orphan*/  tm; TYPE_5__ bl_info; int /*<<< orphan*/  data_sm; TYPE_3__ tl_info; int /*<<< orphan*/  nb_tm; TYPE_8__ nb_info; TYPE_9__ info; } ;
struct disk_device_details {int dummy; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 void* data_block_dec ; 
 void* data_block_equal ; 
 void* data_block_inc ; 
 int /*<<< orphan*/  memcpy (TYPE_8__*,TYPE_9__*,int) ; 
 int /*<<< orphan*/  subtree_dec ; 
 int /*<<< orphan*/  subtree_equal ; 
 int /*<<< orphan*/  subtree_inc ; 

__attribute__((used)) static void __setup_btree_details(struct dm_pool_metadata *pmd)
{
	pmd->info.tm = pmd->tm;
	pmd->info.levels = 2;
	pmd->info.value_type.context = pmd->data_sm;
	pmd->info.value_type.size = sizeof(__le64);
	pmd->info.value_type.inc = data_block_inc;
	pmd->info.value_type.dec = data_block_dec;
	pmd->info.value_type.equal = data_block_equal;

	memcpy(&pmd->nb_info, &pmd->info, sizeof(pmd->nb_info));
	pmd->nb_info.tm = pmd->nb_tm;

	pmd->tl_info.tm = pmd->tm;
	pmd->tl_info.levels = 1;
	pmd->tl_info.value_type.context = &pmd->bl_info;
	pmd->tl_info.value_type.size = sizeof(__le64);
	pmd->tl_info.value_type.inc = subtree_inc;
	pmd->tl_info.value_type.dec = subtree_dec;
	pmd->tl_info.value_type.equal = subtree_equal;

	pmd->bl_info.tm = pmd->tm;
	pmd->bl_info.levels = 1;
	pmd->bl_info.value_type.context = pmd->data_sm;
	pmd->bl_info.value_type.size = sizeof(__le64);
	pmd->bl_info.value_type.inc = data_block_inc;
	pmd->bl_info.value_type.dec = data_block_dec;
	pmd->bl_info.value_type.equal = data_block_equal;

	pmd->details_info.tm = pmd->tm;
	pmd->details_info.levels = 1;
	pmd->details_info.value_type.context = NULL;
	pmd->details_info.value_type.size = sizeof(struct disk_device_details);
	pmd->details_info.value_type.inc = NULL;
	pmd->details_info.value_type.dec = NULL;
	pmd->details_info.value_type.equal = NULL;
}