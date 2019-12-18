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
typedef  int /*<<< orphan*/  JSON_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/ * JsonNewObject () ; 
 int /*<<< orphan*/  JsonSet (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * JsonValueGetObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PackToJson (int /*<<< orphan*/ *) ; 

JSON_VALUE *JsonRpcNewResponse(PACK *p)
{
	JSON_VALUE *jv;
	JSON_OBJECT *jo;
	JSON_VALUE *jv2;

	if (p == NULL)
	{
		return NULL;
	}

	jv = JsonNewObject();
	jo = JsonValueGetObject(jv);

	jv2 = PackToJson(p);

	JsonSet(jo, "result", jv2);

	return jv;
}