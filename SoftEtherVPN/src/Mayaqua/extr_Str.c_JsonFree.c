#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  array; TYPE_2__* string; int /*<<< orphan*/  object; } ;
struct TYPE_7__ {TYPE_1__ value; } ;
typedef  TYPE_2__ JSON_VALUE ;

/* Variables and functions */
#define  JSON_TYPE_ARRAY 130 
#define  JSON_TYPE_OBJECT 129 
#define  JSON_TYPE_STRING 128 
 int JsonValueGetType (TYPE_2__*) ; 
 int /*<<< orphan*/  json_array_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_object_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parson_free (TYPE_2__*) ; 

void JsonFree(JSON_VALUE *value) {
	if (value == NULL)
	{
		return;
	}
	switch (JsonValueGetType(value)) {
	case JSON_TYPE_OBJECT:
		json_object_free(value->value.object);
		break;
	case JSON_TYPE_STRING:
		parson_free(value->value.string);
		break;
	case JSON_TYPE_ARRAY:
		json_array_free(value->value.array);
		break;
	default:
		break;
	}
	parson_free(value);
}