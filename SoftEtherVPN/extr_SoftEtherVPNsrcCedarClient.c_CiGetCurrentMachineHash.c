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
 int /*<<< orphan*/  GetMachineName (char*,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  Sha0 (void*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 int /*<<< orphan*/  StrUpper (char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 

void CiGetCurrentMachineHash(void *data)
{
	char name[MAX_PATH];
	char *product_id = NULL;
	// Validate arguments
	if (data == NULL)
	{
		return;
	}

	GetMachineName(name, sizeof(name));

	Trim(name);
	StrUpper(name);

	Sha0(data, name, StrLen(name));
}