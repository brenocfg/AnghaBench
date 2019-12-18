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
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  JSON_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  JsonFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * JsonToPack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * StrToJson (char*) ; 

PACK *JsonStrToPack(char *str)
{
	JSON_VALUE *v = StrToJson(str);
	PACK *ret;

	if (v == NULL)
	{
		return NULL;
	}

	ret = JsonToPack(v);

	JsonFree(v);

	return ret;
}