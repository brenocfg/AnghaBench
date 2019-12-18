#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int id; int offset; } ;
struct TYPE_6__ {TYPE_1__ file; int /*<<< orphan*/  path; } ;
struct TYPE_5__ {TYPE_3__ trunk; } ;
typedef  int /*<<< orphan*/  FDFSTrunkPathInfo ;
typedef  TYPE_2__ FDFSTrunkNode ;
typedef  TYPE_3__ FDFSTrunkFullInfo ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int storage_trunk_node_compare_offset(void *p1, void *p2)
{
	FDFSTrunkFullInfo *pTrunkInfo1;
	FDFSTrunkFullInfo *pTrunkInfo2;
	int result;

	pTrunkInfo1 = &(((FDFSTrunkNode *)p1)->trunk);
	pTrunkInfo2 = &(((FDFSTrunkNode *)p2)->trunk);

	result = memcmp(&(pTrunkInfo1->path), &(pTrunkInfo2->path), \
			sizeof(FDFSTrunkPathInfo));
	if (result != 0)
	{
		return result;
	}

	result = pTrunkInfo1->file.id - pTrunkInfo2->file.id;
	if (result != 0)
	{
		return result;
	}

	return pTrunkInfo1->file.offset - pTrunkInfo2->file.offset;
}