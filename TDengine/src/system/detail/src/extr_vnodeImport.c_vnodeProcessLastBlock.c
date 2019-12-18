#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_19__ {scalar_t__ sversion; int numOfPoints; scalar_t__ last; int /*<<< orphan*/  len; scalar_t__ offset; } ;
struct TYPE_14__ {scalar_t__ last; int numOfBlocks; } ;
struct TYPE_18__ {TYPE_1__ compInfo; scalar_t__ compInfoOffset; } ;
struct TYPE_17__ {TYPE_3__* pObj; } ;
struct TYPE_16__ {size_t vnode; scalar_t__ sversion; } ;
struct TYPE_15__ {int /*<<< orphan*/  hfd; int /*<<< orphan*/  lfd; int /*<<< orphan*/  dfd; } ;
typedef  TYPE_2__ SVnodeObj ;
typedef  TYPE_3__ SMeterObj ;
typedef  TYPE_4__ SImportInfo ;
typedef  TYPE_5__ SHeadInfo ;
typedef  int /*<<< orphan*/  SData ;
typedef  int /*<<< orphan*/  SCompInfo ;
typedef  TYPE_6__ SCompBlock ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read (int /*<<< orphan*/ ,TYPE_6__*,int) ; 
 int /*<<< orphan*/  tsendfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twrite (int /*<<< orphan*/ ,TYPE_6__*,int) ; 
 TYPE_2__* vnodeList ; 
 int /*<<< orphan*/  vnodeReadLastBlockToMem (TYPE_3__*,TYPE_6__*,int /*<<< orphan*/ **) ; 

int vnodeProcessLastBlock(SImportInfo *pImport, SHeadInfo *pHinfo, SData *data[]) {
  SMeterObj *pObj = pImport->pObj;
  SVnodeObj *pVnode = &vnodeList[pObj->vnode];
  SCompBlock lastBlock;
  int        code = 0;

  if (pHinfo->compInfo.last == 0) return 0;

  // read into memory
  uint64_t offset =
      pHinfo->compInfoOffset + (pHinfo->compInfo.numOfBlocks - 1) * sizeof(SCompBlock) + sizeof(SCompInfo);
  lseek(pVnode->hfd, offset, SEEK_SET);
  read(pVnode->hfd, &lastBlock, sizeof(SCompBlock));
  assert(lastBlock.last);

  if (lastBlock.sversion != pObj->sversion) {
    lseek(pVnode->lfd, lastBlock.offset, SEEK_SET);
    lastBlock.offset = lseek(pVnode->dfd, 0, SEEK_END);
    tsendfile(pVnode->dfd, pVnode->lfd, NULL, lastBlock.len);

    lastBlock.last = 0;
    lseek(pVnode->hfd, offset, SEEK_SET);
    twrite(pVnode->hfd, &lastBlock, sizeof(SCompBlock));
  } else {
    vnodeReadLastBlockToMem(pObj, &lastBlock, data);
    pHinfo->compInfo.numOfBlocks--;
    code = lastBlock.numOfPoints;
  }

  return code;
}