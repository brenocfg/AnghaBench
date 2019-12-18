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
typedef  int /*<<< orphan*/  tmp ;
typedef  scalar_t__ UINT ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int MAX_SIZE ; 
 scalar_t__ MsiGetProductInfoA (char*,char*,char*,int*) ; 
 int /*<<< orphan*/  StrCpy (char*,scalar_t__,char*) ; 

bool ViMsiGetProductInfo(char *product_code, char *name, char *buf, UINT size)
{
	UINT ret;
	char tmp[MAX_SIZE];
	DWORD sz;
	// Validate arguments
	if (product_code == NULL || name == NULL || buf == NULL)
	{
		return false;
	}

	sz = sizeof(tmp);

	ret = MsiGetProductInfoA(product_code, name, tmp, &sz);
	if (ret != ERROR_SUCCESS)
	{
		return false;
	}

	StrCpy(buf, size, tmp);

	return true;
}