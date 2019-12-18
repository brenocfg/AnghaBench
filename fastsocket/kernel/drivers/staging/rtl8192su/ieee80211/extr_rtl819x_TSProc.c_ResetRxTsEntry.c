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
struct TYPE_3__ {int RxIndicateSeq; int RxTimeoutIndicateSeq; int /*<<< orphan*/  RxAdmittedBARecord; int /*<<< orphan*/  TsCommonInfo; } ;
typedef  TYPE_1__* PRX_TS_RECORD ;

/* Variables and functions */
 int /*<<< orphan*/  ResetBaEntry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResetTsCommonInfo (int /*<<< orphan*/ *) ; 

void ResetRxTsEntry(PRX_TS_RECORD pTS)
{
	ResetTsCommonInfo(&pTS->TsCommonInfo);
	pTS->RxIndicateSeq = 0xffff; // This indicate the RxIndicateSeq is not used now!!
	pTS->RxTimeoutIndicateSeq = 0xffff; // This indicate the RxTimeoutIndicateSeq is not used now!!
	ResetBaEntry(&pTS->RxAdmittedBARecord);	  // For BA Recepient
}