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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  hash; } ;
typedef  TYPE_1__ SHandleViaTcp ;

/* Variables and functions */
 int /*<<< orphan*/  taosHashUInt64 (int /*<<< orphan*/ ) ; 

void taosInitHandleViaTcp(SHandleViaTcp *handleViaTcp, uint64_t handle) {
  handleViaTcp->handle = handle;
  handleViaTcp->hash = taosHashUInt64(handleViaTcp->handle);
}