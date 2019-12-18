#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_4__ {scalar_t__ count; int /*<<< orphan*/ * values; int /*<<< orphan*/ * names; } ;
typedef  TYPE_1__ JSON_OBJECT ;

/* Variables and functions */
 size_t JSON_RET_ERROR ; 
 size_t JSON_RET_OK ; 
 int /*<<< orphan*/  JsonFree (int /*<<< orphan*/ ) ; 
 size_t JsonGetCount (TYPE_1__*) ; 
 int /*<<< orphan*/  parson_free (int /*<<< orphan*/ ) ; 

UINT JsonDeleteAll(JSON_OBJECT *object) {
	UINT i = 0;
	if (object == NULL) {
		return JSON_RET_ERROR;
	}
	for (i = 0; i < JsonGetCount(object); i++) {
		parson_free(object->names[i]);
		JsonFree(object->values[i]);
	}
	object->count = 0;
	return JSON_RET_OK;
}