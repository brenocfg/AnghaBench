#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  defaultVal; int /*<<< orphan*/  interpoType; } ;
typedef  TYPE_1__ SSqlCmd ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_INTERPO_NONE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tscIsPointInterpQuery (TYPE_1__*) ; 

void tscClearInterpInfo(SSqlCmd* pCmd) {
  if (!tscIsPointInterpQuery(pCmd)) {
    return;
  }

  pCmd->interpoType = TSDB_INTERPO_NONE;
  memset(pCmd->defaultVal, 0, sizeof(pCmd->defaultVal));
}