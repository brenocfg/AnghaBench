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
 char* JsonToStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PackToJson (int /*<<< orphan*/ *) ; 

char *PackToJsonStr(PACK *p)
{
	char *ret;
	JSON_VALUE *json = PackToJson(p);

	ret = JsonToStr(json);

	JsonFree(json);

	return ret;
}