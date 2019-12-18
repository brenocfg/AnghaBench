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
typedef  int /*<<< orphan*/  rand ;
typedef  int /*<<< orphan*/  id_str ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  JSON_VALUE ;
typedef  int /*<<< orphan*/  JSON_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  BinToStr (char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * JsonNewObject () ; 
 int /*<<< orphan*/ * JsonObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JsonSet (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JsonSetStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  Rand (int /*<<< orphan*/ *,int) ; 

JSON_VALUE *ConstructDummyJsonRpcRequest(char *method_name, JSON_VALUE *p)
{
	JSON_VALUE *ret;
	JSON_OBJECT *ret_object;
	UCHAR rand[16];
	char id_str[64];

	Rand(rand, sizeof(rand));

	BinToStr(id_str, sizeof(id_str), rand, sizeof(rand));

	ret = JsonNewObject();
	ret_object = JsonObject(ret);

	JsonSetStr(ret_object, "jsonrpc", "2.0");
	JsonSetStr(ret_object, "method", method_name);
	JsonSet(ret_object, "params", p);
	JsonSetStr(ret_object, "id", id_str);

	return ret;
}