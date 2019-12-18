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
struct TYPE_3__ {int bValid; } ;
struct TYPE_4__ {int bAddBaReqInProgress; int bAddBaReqDelayed; TYPE_1__ TxPendingBARecord; } ;
typedef  TYPE_2__* PTX_TS_RECORD ;

/* Variables and functions */

void BaSetupTimeOut(unsigned long data)
{
	PTX_TS_RECORD	pTxTs = (PTX_TS_RECORD)data;

	pTxTs->bAddBaReqInProgress = false;
	pTxTs->bAddBaReqDelayed = true;
	pTxTs->TxPendingBARecord.bValid = false;
}