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
struct TYPE_2__ {struct bas_cardstate* bas; } ;
struct cardstate {int /*<<< orphan*/  dev; TYPE_1__ hw; } ;
struct bas_cardstate {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BS_ATREADY ; 
 int /*<<< orphan*/  BS_ATTIMER ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  start_cbsend (struct cardstate*) ; 
 int /*<<< orphan*/  update_basstate (struct bas_cardstate*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atrdy_timeout(unsigned long data)
{
	struct cardstate *cs = (struct cardstate *) data;
	struct bas_cardstate *ucs = cs->hw.bas;

	dev_warn(cs->dev, "timeout waiting for HD_READY_SEND_ATDATA\n");

	/* fake the missing signal - what else can I do? */
	update_basstate(ucs, BS_ATREADY, BS_ATTIMER);
	start_cbsend(cs);
}