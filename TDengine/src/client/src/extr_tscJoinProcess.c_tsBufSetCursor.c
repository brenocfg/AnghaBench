#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int vnodeIndex; int /*<<< orphan*/  blockIndex; } ;
struct TYPE_7__ {TYPE_1__ cur; } ;
typedef  TYPE_1__ STSCursor ;
typedef  TYPE_2__ STSBuf ;

/* Variables and functions */
 int /*<<< orphan*/  tsBufGetBlock (TYPE_2__*,int,int /*<<< orphan*/ ) ; 

void tsBufSetCursor(STSBuf* pTSBuf, STSCursor* pCur) {
  if (pTSBuf == NULL || pCur == NULL) {
    return;
  }

  //  assert(pCur->vnodeIndex != -1 && pCur->tsIndex >= 0 && pCur->blockIndex >= 0);
  if (pCur->vnodeIndex != -1) {
    tsBufGetBlock(pTSBuf, pCur->vnodeIndex, pCur->blockIndex);
  }

  pTSBuf->cur = *pCur;
}