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
typedef  int /*<<< orphan*/  JSON_ARRAY ;

/* Variables and functions */
 int /*<<< orphan*/  B64_Encode (char*,void*,int) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int JsonArrayAddStr (int /*<<< orphan*/ *,char*) ; 
 char* ZeroMalloc (int) ; 

UINT JsonArrayAddData(JSON_ARRAY *array, void *data, UINT size)
{
	UINT ret;
	char *b64 = ZeroMalloc(size * 4 + 32);
	B64_Encode(b64, data, size);

	ret = JsonArrayAddStr(array, b64);

	Free(b64);
	return ret;
}