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
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  IPC_MSCHAP_V2_AUTHINFO ;

/* Variables and functions */
 char* CopyStr (char*) ; 
 char* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MIN (scalar_t__,int) ; 
 scalar_t__ MsChapV2VerityPassword (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ Power (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetStrCaseAccordingToBits (char*,scalar_t__) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 scalar_t__ StrLen (char*) ; 

char *MsChapV2DoBruteForce(IPC_MSCHAP_V2_AUTHINFO *d, LIST *password_list)
{
	UINT i;
	// Validate arguments
	if (d == NULL || password_list == NULL)
	{
		return NULL;
	}

	for (i = 0;i < LIST_NUM(password_list);i++)
	{
		char *s = LIST_DATA(password_list, i);
		char tmp[MAX_SIZE];
		UINT j, max;
		UINT len;

		StrCpy(tmp, sizeof(tmp), s);

		len = StrLen(tmp);
		max = Power(2, MIN(len, 9));

		for (j = 0;j < max;j++)
		{
			SetStrCaseAccordingToBits(tmp, j);
			if (MsChapV2VerityPassword(d, tmp))
			{
				return CopyStr(tmp);
			}
		}
	}

	return NULL;
}