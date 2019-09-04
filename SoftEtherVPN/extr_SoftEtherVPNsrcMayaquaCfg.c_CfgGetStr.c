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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int CfgGetUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Malloc (int) ; 
 int /*<<< orphan*/  UniToStr (char*,int,int /*<<< orphan*/ *) ; 

bool CfgGetStr(FOLDER *f, char *name, char *str, UINT size)
{
	wchar_t *tmp;
	UINT tmp_size;
	// Validate arguments
	if (f == NULL || name == NULL || str == NULL)
	{
		return false;
	}

	str[0] = 0;

	// Get unicode string temporarily
	tmp_size = size * 4 + 10; // Just to make sure, a quantity of this amount is secured.
	tmp = Malloc(tmp_size);
	if (CfgGetUniStr(f, name, tmp, tmp_size) == false)
	{
		// Failure
		Free(tmp);
		return false;
	}

	// Copy to the ANSI string
	UniToStr(str, size, tmp);
	Free(tmp);

	return true;
}