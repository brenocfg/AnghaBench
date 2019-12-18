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
struct TYPE_3__ {int bAddBaReqInProgress; int bAddBaReqDelayed; int bUsingBa; int /*<<< orphan*/  TxPendingBARecord; int /*<<< orphan*/  TxAdmittedBARecord; scalar_t__ TxCurSeq; int /*<<< orphan*/  TsCommonInfo; } ;
typedef  TYPE_1__* PTX_TS_RECORD ;

/* Variables and functions */
 int /*<<< orphan*/  ResetBaEntry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResetTsCommonInfo (int /*<<< orphan*/ *) ; 

void ResetTxTsEntry(PTX_TS_RECORD pTS)
{
	ResetTsCommonInfo(&pTS->TsCommonInfo);
	pTS->TxCurSeq = 0;
	pTS->bAddBaReqInProgress = false;
	pTS->bAddBaReqDelayed = false;
	pTS->bUsingBa = false;
	ResetBaEntry(&pTS->TxAdmittedBARecord); //For BA Originator
	ResetBaEntry(&pTS->TxPendingBARecord);
}