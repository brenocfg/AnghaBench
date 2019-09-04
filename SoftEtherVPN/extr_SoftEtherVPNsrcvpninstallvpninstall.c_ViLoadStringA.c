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
typedef  int UINT ;
typedef  int /*<<< orphan*/  HINSTANCE ;

/* Variables and functions */
 char* CopyStr (char*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 scalar_t__ LoadStringA (int /*<<< orphan*/ ,int,char*,int) ; 
 char* Malloc (int) ; 

char *ViLoadStringA(HINSTANCE hInst, UINT id)
{
	UINT tmp_size = 60000;
	char *tmp = Malloc(tmp_size);
	char *ret = NULL;

	if (LoadStringA(hInst, id, tmp, tmp_size) != 0)
	{
		ret = CopyStr(tmp);
	}

	Free(tmp);

	return ret;
}