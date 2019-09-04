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
typedef  int UINT ;
struct TYPE_3__ {char** Token; int NumTokens; } ;
typedef  TYPE_1__ TOKEN_LIST ;

/* Variables and functions */
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 void* Malloc (int) ; 
 int /*<<< orphan*/  StrCpy (char*,int /*<<< orphan*/ ,char*) ; 
 int StrLen (char*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 void* ZeroMalloc (int) ; 
 char* strtok (char*,char*) ; 
 int /*<<< orphan*/  token_lock ; 

TOKEN_LIST *ParseToken(char *src, char *separator)
{
	TOKEN_LIST *ret;
	char *tmp;
	char *str1, *str2;
	UINT len;
	UINT num;
	if (src == NULL)
	{
		ret = ZeroMalloc(sizeof(TOKEN_LIST));
		ret->Token = ZeroMalloc(0);
		return ret;
	}
	if (separator == NULL)
	{
		separator = " ,\t\r\n";
	}
	len = StrLen(src);
	str1 = Malloc(len + 1);
	str2 = Malloc(len + 1);
	StrCpy(str1, 0, src);
	StrCpy(str2, 0, src);

	Lock(token_lock);
	{
		tmp = strtok(str1, separator);
		num = 0;
		while (tmp != NULL)
		{
			num++;
			tmp = strtok(NULL, separator);
		}
		ret = Malloc(sizeof(TOKEN_LIST));
		ret->NumTokens = num;
		ret->Token = (char **)Malloc(sizeof(char *) * num);
		num = 0;
		tmp = strtok(str2, separator);
		while (tmp != NULL)
		{
			ret->Token[num] = (char *)Malloc(StrLen(tmp) + 1);
			StrCpy(ret->Token[num], 0, tmp);
			num++;
			tmp = strtok(NULL, separator);
		}
	}
	Unlock(token_lock);

	Free(str1);
	Free(str2);
	return ret;
}