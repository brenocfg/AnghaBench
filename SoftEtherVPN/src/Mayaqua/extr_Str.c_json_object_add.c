#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int count; int capacity; TYPE_1__** values; int /*<<< orphan*/ ** names; } ;
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
typedef  TYPE_1__ JSON_VALUE ;
typedef  TYPE_2__ JSON_OBJECT ;

/* Variables and functions */
 scalar_t__ JSON_RET_ERROR ; 
 scalar_t__ JSON_RET_OK ; 
 int /*<<< orphan*/ * JsonGet (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  JsonGetWrappingValue (TYPE_2__*) ; 
 scalar_t__ MAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STARTING_CAPACITY ; 
 scalar_t__ json_object_resize (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/ * parson_strdup (char*) ; 

__attribute__((used)) static UINT json_object_add(JSON_OBJECT *object, char *name, JSON_VALUE *value) {
	UINT index = 0;
	if (object == NULL || name == NULL || value == NULL) {
		return JSON_RET_ERROR;
	}
	if (JsonGet(object, name) != NULL) {
		return JSON_RET_ERROR;
	}
	if (object->count >= object->capacity) {
		UINT new_capacity = MAX(object->capacity * 2, STARTING_CAPACITY);
		if (json_object_resize(object, new_capacity) == JSON_RET_ERROR) {
			return JSON_RET_ERROR;
		}
	}
	index = object->count;
	object->names[index] = parson_strdup(name);
	if (object->names[index] == NULL) {
		return JSON_RET_ERROR;
	}
	value->parent = JsonGetWrappingValue(object);
	object->values[index] = value;
	object->count++;
	return JSON_RET_OK;
}