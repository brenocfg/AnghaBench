#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ num; scalar_t__ (* startFp ) () ;} ;

/* Variables and functions */
 int TSDB_MOD_MAX ; 
 int /*<<< orphan*/  dError (char*,int) ; 
 scalar_t__ stub1 () ; 
 TYPE_1__* tsModule ; 

void dnodeStartModuleSpec() {
  for (int mod = 1; mod < TSDB_MOD_MAX; ++mod) {
    if (tsModule[mod].num != 0 && tsModule[mod].startFp) {
      if ((*tsModule[mod].startFp)() != 0) {
        dError("failed to start module:%d", mod);
      }
    }
  }
}