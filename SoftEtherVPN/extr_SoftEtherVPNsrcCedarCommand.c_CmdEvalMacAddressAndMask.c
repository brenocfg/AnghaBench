#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_4__ {int /*<<< orphan*/  (* Write ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ CONSOLE ;

/* Variables and functions */
 int ParseMacAddressAndMask (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniToStr (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

bool CmdEvalMacAddressAndMask(CONSOLE *c, wchar_t *str, void *param)
{
	char tmp[64];
	// Validate arguments
	if(c == NULL || str == NULL)
	{
		return false;
	}

	UniToStr(tmp, sizeof(tmp), str);


	if(ParseMacAddressAndMask(tmp, NULL, NULL, NULL) == false)
	{
		c->Write(c, _UU("CMD_MAC_ADDRESS_AND_MASK_EVAL_FAILED"));
		return false;
	}

	return true;
}