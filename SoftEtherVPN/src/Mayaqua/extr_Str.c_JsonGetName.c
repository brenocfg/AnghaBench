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
struct TYPE_4__ {char** names; } ;
typedef  TYPE_1__ JSON_OBJECT ;

/* Variables and functions */
 size_t JsonGetCount (TYPE_1__*) ; 

char * JsonGetName(JSON_OBJECT *object, UINT index) {
	if (object == NULL || index >= JsonGetCount(object)) {
		return NULL;
	}
	return object->names[index];
}