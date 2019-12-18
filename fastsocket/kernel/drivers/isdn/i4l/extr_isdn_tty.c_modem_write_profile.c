#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lmsn; int /*<<< orphan*/  plmsn; int /*<<< orphan*/  msn; int /*<<< orphan*/  pmsn; int /*<<< orphan*/  mdmreg; int /*<<< orphan*/  profile; } ;
typedef  TYPE_1__ atemu ;
struct TYPE_5__ {scalar_t__ profd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISDN_LMSNLEN ; 
 int /*<<< orphan*/  ISDN_MODEM_NUMREG ; 
 int /*<<< orphan*/  ISDN_MSNLEN ; 
 int /*<<< orphan*/  SIGIO ; 
 TYPE_3__* dev ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void
modem_write_profile(atemu * m)
{
	memcpy(m->profile, m->mdmreg, ISDN_MODEM_NUMREG);
	memcpy(m->pmsn, m->msn, ISDN_MSNLEN);
	memcpy(m->plmsn, m->lmsn, ISDN_LMSNLEN);
	if (dev->profd)
		send_sig(SIGIO, dev->profd, 1);
}