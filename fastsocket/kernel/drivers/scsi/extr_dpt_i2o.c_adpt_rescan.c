#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong ;
typedef  scalar_t__ s32 ;
struct TYPE_7__ {TYPE_1__* host; } ;
typedef  TYPE_2__ adpt_hba ;
struct TYPE_6__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 scalar_t__ adpt_i2o_lct_get (TYPE_2__*) ; 
 scalar_t__ adpt_i2o_reparse_lct (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 adpt_rescan(adpt_hba* pHba)
{
	s32 rcode;
	ulong flags = 0;

	if(pHba->host)
		spin_lock_irqsave(pHba->host->host_lock, flags);
	if ((rcode=adpt_i2o_lct_get(pHba)) < 0)
		goto out;
	if ((rcode=adpt_i2o_reparse_lct(pHba)) < 0)
		goto out;
	rcode = 0;
out:	if(pHba->host)
		spin_unlock_irqrestore(pHba->host->host_lock, flags);
	return rcode;
}