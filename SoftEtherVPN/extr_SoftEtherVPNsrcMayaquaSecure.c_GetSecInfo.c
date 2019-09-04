#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  token_info ;
struct TYPE_5__ {size_t SessionSlotNumber; int /*<<< orphan*/ * Info; int /*<<< orphan*/ * SlotIdList; TYPE_1__* Api; } ;
struct TYPE_4__ {scalar_t__ (* C_GetTokenInfo ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ SECURE ;
typedef  int /*<<< orphan*/  CK_TOKEN_INFO ;

/* Variables and functions */
 scalar_t__ CKR_OK ; 
 int /*<<< orphan*/ * TokenInfoToSecInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void GetSecInfo(SECURE *sec)
{
	CK_TOKEN_INFO token_info;
	// Validate arguments
	if (sec == NULL)
	{
		return;
	}
	if (sec->Info != NULL)
	{
		return;
	}

	// Acquisition
	Zero(&token_info, sizeof(token_info));
	if (sec->Api->C_GetTokenInfo(sec->SlotIdList[sec->SessionSlotNumber], &token_info) != CKR_OK)
	{
		// Failure
		return;
	}

	sec->Info = TokenInfoToSecInfo(&token_info);
}