#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
typedef  int int32_t ;
struct TYPE_8__ {scalar_t__ tag; } ;
struct TYPE_9__ {scalar_t__ order; } ;
struct TYPE_11__ {TYPE_1__ block; TYPE_2__ cur; int /*<<< orphan*/  f; } ;
struct TYPE_10__ {scalar_t__ offset; scalar_t__ compLen; int numOfBlocks; } ;
typedef  TYPE_3__ STSVnodeBlockInfo ;
typedef  TYPE_4__ STSBuf ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ TSQL_SO_ASC ; 
 scalar_t__ fseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * readDataFromDisk (TYPE_4__*,scalar_t__,int) ; 

__attribute__((used)) static int32_t tsBufFindBlockByTag(STSBuf* pTSBuf, STSVnodeBlockInfo* pBlockInfo, int64_t tag) {
  bool decomp = false;

  int64_t offset = 0;
  if (pTSBuf->cur.order == TSQL_SO_ASC) {
    offset = pBlockInfo->offset;
  } else {  // reversed traverse starts from the end of block
    offset = pBlockInfo->offset + pBlockInfo->compLen;
  }

  if (fseek(pTSBuf->f, offset, SEEK_SET) != 0) {
    return -1;
  }

  for (int32_t i = 0; i < pBlockInfo->numOfBlocks; ++i) {
    if (readDataFromDisk(pTSBuf, pTSBuf->cur.order, decomp) == NULL) {
      return -1;
    }

    if (pTSBuf->block.tag == tag) {
      return i;
    }
  }

  return -1;
}