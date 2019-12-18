#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char** names; scalar_t__ count; scalar_t__ capacity; int /*<<< orphan*/ ** values; int /*<<< orphan*/ * wrapping_value; } ;
typedef  int /*<<< orphan*/  JSON_VALUE ;
typedef  TYPE_1__ JSON_OBJECT ;

/* Variables and functions */
 scalar_t__ parson_malloc (int) ; 

__attribute__((used)) static JSON_OBJECT * json_object_init(JSON_VALUE *wrapping_value) {
	JSON_OBJECT *new_obj = (JSON_OBJECT*)parson_malloc(sizeof(JSON_OBJECT));
	if (new_obj == NULL) {
		return NULL;
	}
	new_obj->wrapping_value = wrapping_value;
	new_obj->names = (char**)NULL;
	new_obj->values = (JSON_VALUE**)NULL;
	new_obj->capacity = 0;
	new_obj->count = 0;
	return new_obj;
}