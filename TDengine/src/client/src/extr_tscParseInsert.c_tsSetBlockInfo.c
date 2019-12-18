#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_6__ {int /*<<< orphan*/  sversion; int /*<<< orphan*/  uid; int /*<<< orphan*/  sid; } ;
struct TYPE_5__ {int /*<<< orphan*/  numOfRows; int /*<<< orphan*/  sversion; int /*<<< orphan*/  uid; int /*<<< orphan*/  sid; } ;
typedef  TYPE_1__ SShellSubmitBlock ;
typedef  TYPE_2__ SMeterMeta ;

/* Variables and functions */

__attribute__((used)) static void tsSetBlockInfo(SShellSubmitBlock *pBlocks, const SMeterMeta *pMeterMeta, int32_t numOfRows) {
  pBlocks->sid = pMeterMeta->sid;
  pBlocks->uid = pMeterMeta->uid;
  pBlocks->sversion = pMeterMeta->sversion;
  pBlocks->numOfRows += numOfRows;
}