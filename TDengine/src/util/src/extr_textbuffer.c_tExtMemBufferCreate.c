#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tFlushoutInfo ;
typedef  int /*<<< orphan*/  tFilePage ;
struct TYPE_7__ {int nAllocSize; int /*<<< orphan*/ * pFlushoutInfo; scalar_t__ nLength; } ;
struct TYPE_8__ {TYPE_1__ flushoutData; void* nPageSize; scalar_t__ nFileSize; scalar_t__ numOfElemsInFile; } ;
typedef  TYPE_2__ tFileMeta ;
struct TYPE_9__ {int nPageSize; int nMaxSizeInPages; int nElemSize; int numOfElemsPerPage; int /*<<< orphan*/  pColModel; TYPE_2__ fileMeta; int /*<<< orphan*/  dataFilePath; } ;
typedef  TYPE_3__ tExtMemBuffer ;
struct TYPE_10__ {int /*<<< orphan*/  numOfCols; int /*<<< orphan*/  pFields; } ;
typedef  TYPE_4__ tColModel ;
typedef  int int32_t ;

/* Variables and functions */
 int ALIGN8 (int) ; 
 void* DEFAULT_PAGE_SIZE ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  tColModelCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void tExtMemBufferCreate(tExtMemBuffer **pMemBuffer, int32_t nBufferSize, int32_t elemSize, const char *tmpDataFilePath,
                         tColModel *pModel) {
  (*pMemBuffer) = (tExtMemBuffer *)calloc(1, sizeof(tExtMemBuffer));

  (*pMemBuffer)->nPageSize = DEFAULT_PAGE_SIZE;
  (*pMemBuffer)->nMaxSizeInPages = ALIGN8(nBufferSize) / (*pMemBuffer)->nPageSize;
  (*pMemBuffer)->nElemSize = elemSize;

  (*pMemBuffer)->numOfElemsPerPage = ((*pMemBuffer)->nPageSize - sizeof(tFilePage)) / (*pMemBuffer)->nElemSize;

  strcpy((*pMemBuffer)->dataFilePath, tmpDataFilePath);

  tFileMeta *pFMeta = &(*pMemBuffer)->fileMeta;

  pFMeta->numOfElemsInFile = 0;
  pFMeta->nFileSize = 0;
  pFMeta->nPageSize = DEFAULT_PAGE_SIZE;

  pFMeta->flushoutData.nAllocSize = 4;
  pFMeta->flushoutData.nLength = 0;
  pFMeta->flushoutData.pFlushoutInfo = (tFlushoutInfo *)calloc(4, sizeof(tFlushoutInfo));

  (*pMemBuffer)->pColModel = tColModelCreate(pModel->pFields, pModel->numOfCols, (*pMemBuffer)->numOfElemsPerPage);
}