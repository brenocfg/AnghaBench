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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  JSON_VALUE ;
typedef  int /*<<< orphan*/  JSON_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/ * JsonNewObject () ; 
 int /*<<< orphan*/  JsonSet (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JsonSetNumber (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JsonSetUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * JsonValueGetObject (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,char*,int,...) ; 
 scalar_t__ UniIsEmptyStr (int /*<<< orphan*/ *) ; 

JSON_VALUE *JsonRpcNewError(int code, wchar_t *message)
{
	wchar_t msg[MAX_PATH];
	JSON_VALUE *jv;
	JSON_OBJECT *jo;
	JSON_VALUE *jv2;
	JSON_OBJECT *jo2;

	if (UniIsEmptyStr(message))
	{
		UniFormat(msg, sizeof(msg), L"Error code %u", code);
	}
	else
	{
		UniFormat(msg, sizeof(msg), L"Error code %u: %s", code, message);
	}

	jv = JsonNewObject();
	jo = JsonValueGetObject(jv);

	jv2 = JsonNewObject();
	jo2 = JsonValueGetObject(jv2);

	JsonSet(jo, "error", jv2);

	JsonSetNumber(jo2, "code", (UINT64)code);
	JsonSetUniStr(jo2, "message", msg);

	return jv;
}