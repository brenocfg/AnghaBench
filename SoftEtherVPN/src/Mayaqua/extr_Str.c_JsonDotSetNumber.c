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
typedef  int /*<<< orphan*/  UINT64 ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  JSON_VALUE ;
typedef  int /*<<< orphan*/  JSON_OBJECT ;

/* Variables and functions */
 scalar_t__ JSON_RET_ERROR ; 
 scalar_t__ JSON_RET_OK ; 
 scalar_t__ JsonDotSet (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JsonFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * JsonNewNumber (int /*<<< orphan*/ ) ; 

UINT JsonDotSetNumber(JSON_OBJECT *object, char *name, UINT64 number) {
	JSON_VALUE *value = JsonNewNumber(number);
	if (value == NULL) {
		return JSON_RET_ERROR;
	}
	if (JsonDotSet(object, name, value) == JSON_RET_ERROR) {
		JsonFree(value);
		return JSON_RET_ERROR;
	}
	return JSON_RET_OK;
}