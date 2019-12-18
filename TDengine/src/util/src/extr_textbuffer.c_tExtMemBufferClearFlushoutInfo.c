#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tFlushoutInfo ;
struct TYPE_5__ {int nAllocSize; int /*<<< orphan*/  pFlushoutInfo; scalar_t__ nLength; } ;
struct TYPE_6__ {TYPE_1__ flushoutData; } ;
typedef  TYPE_2__ tFileMeta ;
struct TYPE_7__ {TYPE_2__ fileMeta; } ;
typedef  TYPE_3__ tExtMemBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tExtMemBufferClearFlushoutInfo(tExtMemBuffer *pMemBuffer) {
  tFileMeta *pFileMeta = &pMemBuffer->fileMeta;

  pFileMeta->flushoutData.nLength = 0;
  memset(pFileMeta->flushoutData.pFlushoutInfo, 0, sizeof(tFlushoutInfo) * pFileMeta->flushoutData.nAllocSize);
}