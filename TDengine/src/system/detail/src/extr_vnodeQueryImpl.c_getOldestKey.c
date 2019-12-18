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
typedef  int int64_t ;
typedef  int int32_t ;
struct TYPE_3__ {int daysPerFile; size_t precision; } ;
typedef  TYPE_1__ SVnodeCfg ;

/* Variables and functions */
 int* tsMsPerDay ; 

__attribute__((used)) static int64_t getOldestKey(int32_t numOfFiles, int64_t fileId, SVnodeCfg *pCfg) {
  int64_t duration = pCfg->daysPerFile * tsMsPerDay[pCfg->precision];
  return (fileId - numOfFiles + 1) * duration;
}