#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_5__ {int /*<<< orphan*/  info; } ;
struct TYPE_4__ {TYPE_3__* pData; int /*<<< orphan*/  numOfVnodes; } ;
typedef  int /*<<< orphan*/  STSVnodeBlockInfo ;
typedef  TYPE_1__ STSBuf ;

/* Variables and functions */
 int tsBufFindVnodeIndexFromId (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

STSVnodeBlockInfo* tsBufGetVnodeBlockInfo(STSBuf* pTSBuf, int32_t vnodeId) {
  int32_t j = tsBufFindVnodeIndexFromId(pTSBuf->pData, pTSBuf->numOfVnodes, vnodeId);
  if (j == -1) {
    return NULL;
  }

  return &pTSBuf->pData[j].info;
}