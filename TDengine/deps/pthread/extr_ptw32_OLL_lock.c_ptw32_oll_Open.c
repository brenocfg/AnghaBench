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
struct TYPE_3__ {int /*<<< orphan*/  proxyRoot; } ;
typedef  TYPE_1__ ptw32_oll_csnzi_t ;

/* Variables and functions */
 int /*<<< orphan*/  ptw32_oll_snziRoot_openAndZero ; 

void
ptw32_oll_Open(ptw32_oll_csnzi_t* csnziPtr)
{
  csnziPtr->proxyRoot = ptw32_oll_snziRoot_openAndZero;
}