#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ status; } ;
struct TYPE_14__ {scalar_t__ store_path_index; } ;
struct TYPE_17__ {TYPE_1__ path; } ;
struct TYPE_16__ {TYPE_6__ trunk; struct TYPE_16__* next; } ;
struct TYPE_15__ {int size; TYPE_3__* head; } ;
typedef  TYPE_2__ FDFSTrunkSlot ;
typedef  TYPE_3__ FDFSTrunkNode ;
typedef  TYPE_4__ FDFSTrunkFullInfo ;

/* Variables and functions */
 scalar_t__ FDFS_TRUNK_STATUS_HOLD ; 
 int /*<<< orphan*/  STORAGE_TRUNK_CHECK_STATUS () ; 
 scalar_t__ avl_tree_find_ge (scalar_t__,TYPE_2__*) ; 
 int const g_slot_min_size ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ tree_info_by_sizes ; 
 int trunk_add_free_block (TYPE_3__*,int) ; 
 TYPE_3__* trunk_create_trunk_file (scalar_t__,int*) ; 
 int /*<<< orphan*/  trunk_delete_size_tree_entry (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  trunk_free_block_delete (TYPE_6__*) ; 
 int /*<<< orphan*/  trunk_mem_lock ; 
 int trunk_split (TYPE_3__*,int const) ; 

int trunk_alloc_space(const int size, FDFSTrunkFullInfo *pResult)
{
	FDFSTrunkSlot target_slot;
	FDFSTrunkSlot *pSlot;
	FDFSTrunkNode *pPreviousNode;
	FDFSTrunkNode *pTrunkNode;
	int result;

	STORAGE_TRUNK_CHECK_STATUS();

	target_slot.size = (size > g_slot_min_size) ? size : g_slot_min_size;
	target_slot.head = NULL;

	pPreviousNode = NULL;
	pTrunkNode = NULL;
	pthread_mutex_lock(&trunk_mem_lock);
	while (1)
	{
		pSlot = (FDFSTrunkSlot *)avl_tree_find_ge(tree_info_by_sizes \
			 + pResult->path.store_path_index, &target_slot);
		if (pSlot == NULL)
		{
			break;
		}

		pPreviousNode = NULL;
		pTrunkNode = pSlot->head;
		while (pTrunkNode != NULL && \
			pTrunkNode->trunk.status == FDFS_TRUNK_STATUS_HOLD)
		{
			pPreviousNode = pTrunkNode;
			pTrunkNode = pTrunkNode->next;
		}

		if (pTrunkNode != NULL)
		{
			break;
		}

		target_slot.size = pSlot->size + 1;
	}

	if (pTrunkNode != NULL)
	{
		if (pPreviousNode == NULL)
		{
			pSlot->head = pTrunkNode->next;
			if (pSlot->head == NULL)
			{
				trunk_delete_size_tree_entry(pResult->path. \
					store_path_index, pSlot);
			}
		}
		else
		{
			pPreviousNode->next = pTrunkNode->next;
		}

		trunk_free_block_delete(&(pTrunkNode->trunk));
	}
	else
	{
		pTrunkNode = trunk_create_trunk_file(pResult->path. \
					store_path_index, &result);
		if (pTrunkNode == NULL)
		{
			pthread_mutex_unlock(&trunk_mem_lock);
			return result;
		}
	}
	pthread_mutex_unlock(&trunk_mem_lock);

	result = trunk_split(pTrunkNode, size);
	if (result != 0)
	{
		return result;
	}

	pTrunkNode->trunk.status = FDFS_TRUNK_STATUS_HOLD;
	result = trunk_add_free_block(pTrunkNode, true);
	if (result == 0)
	{
		memcpy(pResult, &(pTrunkNode->trunk), \
			sizeof(FDFSTrunkFullInfo));
	}

	return result;
}