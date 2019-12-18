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
typedef  size_t u8 ;
struct TYPE_3__ {size_t* Addr; size_t TClasProc; size_t TClasNum; int /*<<< orphan*/ * TClass; int /*<<< orphan*/  TSpec; } ;
typedef  int /*<<< orphan*/  TSPEC_BODY ;
typedef  int /*<<< orphan*/  QOS_TCLAS ;
typedef  TYPE_1__* PTS_COMMON_INFO ;
typedef  int /*<<< orphan*/ * PTSPEC_BODY ;
typedef  scalar_t__ PQOS_TCLAS ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (size_t*,size_t*,int) ; 

void MakeTSEntry(
		PTS_COMMON_INFO	pTsCommonInfo,
		u8*		Addr,
		PTSPEC_BODY	pTSPEC,
		PQOS_TCLAS	pTCLAS,
		u8		TCLAS_Num,
		u8		TCLAS_Proc
	)
{
	u8	count;

	if(pTsCommonInfo == NULL)
		return;

	memcpy(pTsCommonInfo->Addr, Addr, 6);

	if(pTSPEC != NULL)
		memcpy((u8*)(&(pTsCommonInfo->TSpec)), (u8*)pTSPEC, sizeof(TSPEC_BODY));

	for(count = 0; count < TCLAS_Num; count++)
		memcpy((u8*)(&(pTsCommonInfo->TClass[count])), (u8*)pTCLAS, sizeof(QOS_TCLAS));

	pTsCommonInfo->TClasProc = TCLAS_Proc;
	pTsCommonInfo->TClasNum = TCLAS_Num;
}