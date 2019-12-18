#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  tag; } ;
struct TYPE_12__ {scalar_t__ rawBuf; } ;
struct TYPE_14__ {size_t vnodeIndex; int tsIndex; } ;
struct TYPE_15__ {TYPE_3__ tsData; TYPE_2__* pData; TYPE_7__ block; TYPE_5__ cur; } ;
struct TYPE_13__ {int vnode; int /*<<< orphan*/  tag; int /*<<< orphan*/  ts; } ;
struct TYPE_10__ {int vnode; } ;
struct TYPE_11__ {TYPE_1__ info; } ;
typedef  int /*<<< orphan*/  TSKEY ;
typedef  TYPE_4__ STSElem ;
typedef  TYPE_5__ STSCursor ;
typedef  TYPE_6__ STSBuf ;
typedef  TYPE_7__ STSBlock ;

/* Variables and functions */
 int TSDB_KEYSIZE ; 

STSElem tsBufGetElem(STSBuf* pTSBuf) {
  STSElem    elem1 = {.vnode = -1};
  STSCursor* pCur = &pTSBuf->cur;

  if (pTSBuf == NULL || pCur->vnodeIndex < 0) {
    return elem1;
  }

  STSBlock* pBlock = &pTSBuf->block;

  elem1.vnode = pTSBuf->pData[pCur->vnodeIndex].info.vnode;
  elem1.ts = *(TSKEY*)(pTSBuf->tsData.rawBuf + pCur->tsIndex * TSDB_KEYSIZE);
  elem1.tag = pBlock->tag;

  return elem1;
}