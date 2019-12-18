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
typedef  int /*<<< orphan*/ * ifnet_t ;
typedef  TYPE_1__* ifmultiaddr_t ;
struct TYPE_3__ {int /*<<< orphan*/ * ifma_ifp; } ;

/* Variables and functions */

ifnet_t
ifmaddr_ifnet(ifmultiaddr_t ifma)
{
	return ((ifma == NULL) ? NULL : ifma->ifma_ifp);
}