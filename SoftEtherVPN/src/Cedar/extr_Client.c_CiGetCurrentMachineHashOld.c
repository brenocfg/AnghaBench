#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  GetMachineName (char*,int) ; 
 int MAX_PATH ; 
 char* MsRegReadStr (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  REG_LOCAL_MACHINE ; 
 int /*<<< orphan*/  Sha0 (void*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 int /*<<< orphan*/  StrUpper (char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 

void CiGetCurrentMachineHashOld(void *data)
{
	char name[MAX_PATH];
	char *product_id = NULL;
	// Validate arguments
	if (data == NULL)
	{
		return;
	}

#ifdef	OS_WIN32
	// Product ID
	product_id = MsRegReadStr(REG_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "ProductId");
	if (product_id == NULL)
	{
		product_id = MsRegReadStr(REG_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion", "ProductId");
	}

	StrCpy(name, sizeof(name), product_id);

	Free(product_id);

#else	// OS_WIN32
	GetMachineName(name, sizeof(name));
#endif	// OS_WIN32

	Trim(name);
	StrUpper(name);

	Sha0(data, name, StrLen(name));
}