#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ SSqlCmd ;

/* Variables and functions */
 scalar_t__ QUERY_IS_STABLE_QUERY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscFieldInfoCalOffset (TYPE_1__*) ; 
 int /*<<< orphan*/  tscFieldInfoUpdateOffset (TYPE_1__*) ; 

void setColumnOffsetValueInResultset(SSqlCmd* pCmd) {
  if (QUERY_IS_STABLE_QUERY(pCmd->type)) {
    tscFieldInfoUpdateOffset(pCmd);
  } else {
    tscFieldInfoCalOffset(pCmd);
  }
}