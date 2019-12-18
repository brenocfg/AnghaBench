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
struct TYPE_3__ {scalar_t__ maxSessions; scalar_t__ cacheBlockSize; int replications; scalar_t__ daysPerFile; scalar_t__ daysToKeep; } ;
typedef  TYPE_1__ SVnodeCfg ;

/* Variables and functions */

bool vnodeIsValidVnodeCfg(SVnodeCfg* pCfg) {
  if (pCfg == NULL) return false;

  if (pCfg->maxSessions <= 0 || pCfg->cacheBlockSize <= 0 || pCfg->replications <= 0 || pCfg->replications > 20 ||
      pCfg->daysPerFile <= 0 || pCfg->daysToKeep <= 0) {
    return false;
  }

  return true;
}