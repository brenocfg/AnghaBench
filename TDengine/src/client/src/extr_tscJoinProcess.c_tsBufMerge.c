#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
typedef  scalar_t__ int64_t ;
typedef  int int32_t ;
struct TYPE_13__ {scalar_t__ numOfVnodes; int numOfAlloc; scalar_t__ fileSize; scalar_t__ numOfTotal; int /*<<< orphan*/  f; TYPE_2__* pData; } ;
struct TYPE_11__ {int vnode; scalar_t__ offset; scalar_t__ compLen; scalar_t__ numOfBlocks; } ;
struct TYPE_12__ {TYPE_1__ info; scalar_t__ len; } ;
typedef  TYPE_2__ STSVnodeBlockInfoEx ;
typedef  TYPE_3__ STSBuf ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 scalar_t__ TS_COMP_FILE_VNODE_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 scalar_t__ fseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fsendfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ getDataStartOffset () ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 TYPE_2__* realloc (TYPE_2__*,int) ; 
 int sendfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsBufFlush (TYPE_3__*) ; 

int32_t tsBufMerge(STSBuf* pDestBuf, const STSBuf* pSrcBuf, int32_t vnodeId) {
  if (pDestBuf == NULL || pSrcBuf == NULL || pSrcBuf->numOfVnodes <= 0) {
    return 0;
  }

  if (pDestBuf->numOfVnodes + pSrcBuf->numOfVnodes > TS_COMP_FILE_VNODE_MAX) {
    return -1;
  }

  // src can only have one vnode index
  if (pSrcBuf->numOfVnodes > 1) {
    return -1;
  }

  // there are data in buffer, flush to disk first
  tsBufFlush(pDestBuf);

  // compared with the last vnode id
  if (vnodeId != pDestBuf->pData[pDestBuf->numOfVnodes - 1].info.vnode) {
    int32_t oldSize = pDestBuf->numOfVnodes;
    int32_t newSize = oldSize + pSrcBuf->numOfVnodes;

    if (pDestBuf->numOfAlloc < newSize) {
      pDestBuf->numOfAlloc = newSize;

      STSVnodeBlockInfoEx* tmp = realloc(pDestBuf->pData, sizeof(STSVnodeBlockInfoEx) * newSize);
      if (tmp == NULL) {
        return -1;
      }

      pDestBuf->pData = tmp;
    }

    // directly copy the vnode index information
    memcpy(&pDestBuf->pData[oldSize], pSrcBuf->pData, (size_t)pSrcBuf->numOfVnodes * sizeof(STSVnodeBlockInfoEx));

    // set the new offset value
    for (int32_t i = 0; i < pSrcBuf->numOfVnodes; ++i) {
      STSVnodeBlockInfoEx* pBlockInfoEx = &pDestBuf->pData[i + oldSize];
      pBlockInfoEx->info.offset = (pSrcBuf->pData[i].info.offset - getDataStartOffset()) + pDestBuf->fileSize;
      pBlockInfoEx->info.vnode = vnodeId;
    }

    pDestBuf->numOfVnodes = newSize;
  } else {
    STSVnodeBlockInfoEx* pBlockInfoEx = &pDestBuf->pData[pDestBuf->numOfVnodes - 1];
    pBlockInfoEx->len += pSrcBuf->pData[0].len;
    pBlockInfoEx->info.numOfBlocks += pSrcBuf->pData[0].info.numOfBlocks;
    pBlockInfoEx->info.compLen += pSrcBuf->pData[0].info.compLen;
    pBlockInfoEx->info.vnode = vnodeId;
  }

  int64_t r = fseek(pDestBuf->f, 0, SEEK_END);
  assert(r == 0);

  int64_t offset = getDataStartOffset();
  int32_t size = pSrcBuf->fileSize - offset;

#ifdef LINUX
  ssize_t rc = sendfile(fileno(pDestBuf->f), fileno(pSrcBuf->f), &offset, size);
#else
  ssize_t rc = fsendfile(pDestBuf->f, pSrcBuf->f, &offset, size);
#endif
  if (rc == -1) {
    printf("%s\n", strerror(errno));
    return -1;
  }

  if (rc != size) {
    printf("%s\n", strerror(errno));
    return -1;
  }

  pDestBuf->numOfTotal += pSrcBuf->numOfTotal;

  return 0;
}