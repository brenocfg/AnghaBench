#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_13__ {TYPE_1__** values; int /*<<< orphan*/ * names; } ;
struct TYPE_12__ {int /*<<< orphan*/ * parent; } ;
typedef  TYPE_1__ JSON_VALUE ;
typedef  TYPE_2__ JSON_OBJECT ;

/* Variables and functions */
 size_t JSON_RET_ERROR ; 
 size_t JSON_RET_OK ; 
 int /*<<< orphan*/  JsonFree (TYPE_1__*) ; 
 TYPE_1__* JsonGet (TYPE_2__*,char*) ; 
 size_t JsonGetCount (TYPE_2__*) ; 
 int /*<<< orphan*/ * JsonGetWrappingValue (TYPE_2__*) ; 
 size_t json_object_add (TYPE_2__*,char*,TYPE_1__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

UINT JsonSet(JSON_OBJECT *object, char *name, JSON_VALUE *value) {
	UINT i = 0;
	JSON_VALUE *old_value;
	if (object == NULL || name == NULL || value == NULL || value->parent != NULL) {
		return JSON_RET_ERROR;
	}
	old_value = JsonGet(object, name);
	if (old_value != NULL) { /* free and overwrite old value */
		JsonFree(old_value);
		for (i = 0; i < JsonGetCount(object); i++) {
			if (strcmp(object->names[i], name) == 0) {
				value->parent = JsonGetWrappingValue(object);
				object->values[i] = value;
				return JSON_RET_OK;
			}
		}
	}
	/* add new key value pair */
	return json_object_add(object, name, value);
}