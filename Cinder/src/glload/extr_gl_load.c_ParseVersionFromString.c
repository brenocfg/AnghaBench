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
typedef  scalar_t__ ptrdiff_t ;

/* Variables and functions */
 int atoi (char*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static void ParseVersionFromString(int *pOutMajor, int *pOutMinor, const char *strVersion)
{
	const char *strDotPos = NULL;
	int iLength = 0;
	char strWorkBuff[10];
	*pOutMinor = 0;
	*pOutMajor = 0;

	strDotPos = strchr(strVersion, '.');
	if(!strDotPos)
		return;

	iLength = (int)((ptrdiff_t)strDotPos - (ptrdiff_t)strVersion);
	strncpy(strWorkBuff, strVersion, iLength);
	strWorkBuff[iLength] = '\0';

	*pOutMajor = atoi(strWorkBuff);
	strDotPos = strchr(strVersion + iLength + 1, ' ');
	if(!strDotPos)
	{
		/*No extra data. Take the whole rest of the string.*/
		strcpy(strWorkBuff, strVersion + iLength + 1);
	}
	else
	{
		/*Copy only up until the space.*/
		int iLengthMinor = (int)((ptrdiff_t)strDotPos - (ptrdiff_t)strVersion);
		iLengthMinor = iLengthMinor - (iLength + 1);
		strncpy(strWorkBuff, strVersion + iLength + 1, iLengthMinor);
		strWorkBuff[iLengthMinor] = '\0';
	}

	*pOutMinor = atoi(strWorkBuff);
}