#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* ulpWord; } ;
struct TYPE_4__ {scalar_t__ ulpStatus; TYPE_1__ un; } ;
struct lpfc_iocbq {TYPE_2__ iocb; } ;
struct lpfc_hba {int dummy; } ;

/* Variables and functions */
 scalar_t__ IOSTAT_FABRIC_RJT ; 
 scalar_t__ RJT_LOGIN_REQUIRED ; 

__attribute__((used)) static int
lpfc_fabric_login_reqd(struct lpfc_hba *phba,
		struct lpfc_iocbq *cmdiocb,
		struct lpfc_iocbq *rspiocb)
{

	if ((rspiocb->iocb.ulpStatus != IOSTAT_FABRIC_RJT) ||
		(rspiocb->iocb.un.ulpWord[4] != RJT_LOGIN_REQUIRED))
		return 0;
	else
		return 1;
}