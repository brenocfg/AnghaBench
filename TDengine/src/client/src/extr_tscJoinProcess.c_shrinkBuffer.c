#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int allocSize; int threshold; int /*<<< orphan*/  rawBuf; } ;
typedef  TYPE_1__ STSList ;

/* Variables and functions */
 int MEM_BUF_SIZE ; 
 int /*<<< orphan*/  realloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void shrinkBuffer(STSList* ptsData) {
  // shrink tmp buffer size if it consumes too many memory compared to the pre-defined size
  if (ptsData->allocSize >= ptsData->threshold * 2) {
    ptsData->rawBuf = realloc(ptsData->rawBuf, MEM_BUF_SIZE);
    ptsData->allocSize = MEM_BUF_SIZE;
  }
}