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

/* Variables and functions */
 int B64_Decode (void*,char*,int) ; 
 int /*<<< orphan*/  Copy (char*,char*,int) ; 
 int /*<<< orphan*/  Free (char*) ; 
 char* Malloc (int) ; 
 int /*<<< orphan*/  Safe64ToBase64 (char*) ; 
 int StrLen (char*) ; 

UINT DecodeSafe64(void *dst, char *src, UINT src_strlen)
{
	char *tmp;
	UINT ret;
	if (dst == NULL || src == NULL)
	{
		return 0;
	}

	if (src_strlen == 0)
	{
		src_strlen = StrLen(src);
	}

	tmp = Malloc(src_strlen + 1);
	Copy(tmp, src, src_strlen);
	tmp[src_strlen] = 0;
	Safe64ToBase64(tmp);

	ret = B64_Decode(dst, tmp, src_strlen);
	Free(tmp);

	return ret;
}