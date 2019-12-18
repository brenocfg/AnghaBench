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
struct socket {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dom_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 TYPE_1__* ndrvdomain ; 
 int /*<<< orphan*/  socantsendmore (struct socket*) ; 

__attribute__((used)) static int
ndrv_shutdown(struct socket *so)
{
	LCK_MTX_ASSERT(ndrvdomain->dom_mtx, LCK_MTX_ASSERT_OWNED);
	socantsendmore(so);
	return 0;
}