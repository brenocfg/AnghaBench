#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int cstat; } ;
struct TYPE_7__ {TYPE_1__ cmd; } ;
struct TYPE_6__ {TYPE_3__ scsw; } ;
struct chsc_request {TYPE_2__ irb; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int EPERM ; 
 int SCHN_STAT_CHAIN_CHECK ; 
 int SCHN_STAT_CHN_CTRL_CHK ; 
 int SCHN_STAT_CHN_DATA_CHK ; 
 int SCHN_STAT_PROG_CHECK ; 
 int SCHN_STAT_PROT_CHECK ; 
 int SCSW_STCTL_STATUS_PEND ; 
 int scsw_cstat (TYPE_3__*) ; 
 int scsw_stctl (TYPE_3__*) ; 

__attribute__((used)) static int chsc_examine_irb(struct chsc_request *request)
{
	int backed_up;

	if (!(scsw_stctl(&request->irb.scsw) & SCSW_STCTL_STATUS_PEND))
		return -EIO;
	backed_up = scsw_cstat(&request->irb.scsw) & SCHN_STAT_CHAIN_CHECK;
	request->irb.scsw.cmd.cstat &= ~SCHN_STAT_CHAIN_CHECK;
	if (scsw_cstat(&request->irb.scsw) == 0)
		return 0;
	if (!backed_up)
		return 0;
	if (scsw_cstat(&request->irb.scsw) & SCHN_STAT_PROG_CHECK)
		return -EIO;
	if (scsw_cstat(&request->irb.scsw) & SCHN_STAT_PROT_CHECK)
		return -EPERM;
	if (scsw_cstat(&request->irb.scsw) & SCHN_STAT_CHN_DATA_CHK)
		return -EAGAIN;
	if (scsw_cstat(&request->irb.scsw) & SCHN_STAT_CHN_CTRL_CHK)
		return -EAGAIN;
	return -EIO;
}