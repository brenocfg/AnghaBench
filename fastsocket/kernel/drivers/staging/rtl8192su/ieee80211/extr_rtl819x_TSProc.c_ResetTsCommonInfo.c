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
struct TYPE_3__ {scalar_t__ TClasNum; scalar_t__ TClasProc; int /*<<< orphan*/  TClass; int /*<<< orphan*/  TSpec; int /*<<< orphan*/ * Addr; } ;
typedef  int /*<<< orphan*/  TSPEC_BODY ;
typedef  int /*<<< orphan*/  QOS_TCLAS ;
typedef  TYPE_1__* PTS_COMMON_INFO ;

/* Variables and functions */
 int TCLAS_NUM ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void ResetTsCommonInfo(PTS_COMMON_INFO	pTsCommonInfo)
{
	memset(pTsCommonInfo->Addr, 0, 6);
	memset(&pTsCommonInfo->TSpec, 0, sizeof(TSPEC_BODY));
	memset(&pTsCommonInfo->TClass, 0, sizeof(QOS_TCLAS)*TCLAS_NUM);
	pTsCommonInfo->TClasProc = 0;
	pTsCommonInfo->TClasNum = 0;
}