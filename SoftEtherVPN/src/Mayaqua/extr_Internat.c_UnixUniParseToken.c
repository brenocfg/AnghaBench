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
struct TYPE_4__ {void* Token; } ;
typedef  TYPE_1__ UNI_TOKEN_LIST ;
typedef  int /*<<< orphan*/  TOKEN_LIST ;

/* Variables and functions */
 char* CopyUniToStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeToken (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ParseToken (char*,char*) ; 
 TYPE_1__* TokenListToUniTokenList (int /*<<< orphan*/ *) ; 
 void* ZeroMalloc (int) ; 

UNI_TOKEN_LIST *UnixUniParseToken(wchar_t *src, wchar_t *separator)
{
	UNI_TOKEN_LIST *ret;
	TOKEN_LIST *t;
	char *src_s;
	char *sep_s;

	// Validate arguments
	if (src == NULL || separator == NULL)
	{
		ret = ZeroMalloc(sizeof(UNI_TOKEN_LIST));
		ret->Token = ZeroMalloc(0);
		return ret;
	}

	src_s = CopyUniToStr(src);
	sep_s = CopyUniToStr(separator);

	t = ParseToken(src_s, sep_s);

	ret = TokenListToUniTokenList(t);
	FreeToken(t);

	Free(src_s);
	Free(sep_s);

	return ret;
}