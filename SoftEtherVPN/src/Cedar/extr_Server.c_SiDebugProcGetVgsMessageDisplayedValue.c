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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int VgsMessageDisplayed; } ;
typedef  TYPE_1__ SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  ToStr (char*,int) ; 
 int VgDoNotPopupMessage () ; 

UINT SiDebugProcGetVgsMessageDisplayedValue(SERVER *s, char *in_str, char *ret_str, UINT ret_str_size)
{
	// Validate arguments
	if (s == NULL || in_str == NULL || ret_str == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

#if	0
	if (VgDoNotPopupMessage() == false)
	{
		ToStr(ret_str, s->VgsMessageDisplayed);
	}
	else
	{
		ToStr(ret_str, 1);
	}
#else
	// Do not show the VGS message in VPN Server of the current version
	ToStr(ret_str, 1);
#endif	

	return ERR_NO_ERROR;
}