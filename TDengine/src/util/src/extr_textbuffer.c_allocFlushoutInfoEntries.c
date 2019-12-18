#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tFlushoutInfo ;
struct TYPE_4__ {int nAllocSize; int /*<<< orphan*/ * pFlushoutInfo; } ;
struct TYPE_5__ {TYPE_1__ flushoutData; } ;
typedef  TYPE_2__ tFileMeta ;

/* Variables and functions */
 int /*<<< orphan*/  pError (char*) ; 
 scalar_t__ realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool allocFlushoutInfoEntries(tFileMeta *pFileMeta) {
  pFileMeta->flushoutData.nAllocSize = pFileMeta->flushoutData.nAllocSize << 1;

  tFlushoutInfo *tmp = (tFlushoutInfo *)realloc(pFileMeta->flushoutData.pFlushoutInfo,
                                                sizeof(tFlushoutInfo) * pFileMeta->flushoutData.nAllocSize);
  if (tmp == NULL) {
    pError("out of memory!\n");
    return false;
  }

  pFileMeta->flushoutData.pFlushoutInfo = tmp;
  return true;
}