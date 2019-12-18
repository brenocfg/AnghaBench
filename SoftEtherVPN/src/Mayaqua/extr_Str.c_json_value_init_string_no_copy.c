#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* string; } ;
struct TYPE_5__ {TYPE_1__ value; int /*<<< orphan*/  type; int /*<<< orphan*/ * parent; } ;
typedef  TYPE_2__ JSON_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_TYPE_STRING ; 
 scalar_t__ parson_malloc (int) ; 

__attribute__((used)) static JSON_VALUE * json_value_init_string_no_copy(char *string) {
	JSON_VALUE *new_value = (JSON_VALUE*)parson_malloc(sizeof(JSON_VALUE));
	if (!new_value) {
		return NULL;
	}
	new_value->parent = NULL;
	new_value->type = JSON_TYPE_STRING;
	new_value->value.string = string;
	return new_value;
}