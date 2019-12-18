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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  JSON_VALUE ;
typedef  int /*<<< orphan*/  JSON_ARRAY ;

/* Variables and functions */
 scalar_t__ JSON_RET_ERROR ; 
 scalar_t__ JSON_RET_OK ; 
 scalar_t__ JsonArrayAdd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JsonFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * JsonNewStr (char*) ; 

UINT JsonArrayAddStr(JSON_ARRAY *array, char *string) {
	JSON_VALUE *value = JsonNewStr(string);
	if (value == NULL) {
		return JSON_RET_ERROR;
	}
	if (JsonArrayAdd(array, value) == JSON_RET_ERROR) {
		JsonFree(value);
		return JSON_RET_ERROR;
	}
	return JSON_RET_OK;
}