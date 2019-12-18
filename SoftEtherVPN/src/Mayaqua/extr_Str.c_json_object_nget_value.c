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
struct TYPE_4__ {int /*<<< orphan*/ ** values; int /*<<< orphan*/ * names; } ;
typedef  int /*<<< orphan*/  JSON_VALUE ;
typedef  TYPE_1__ JSON_OBJECT ;

/* Variables and functions */
 size_t JsonGetCount (TYPE_1__*) ; 
 size_t StrLen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static JSON_VALUE * json_object_nget_value(JSON_OBJECT *object, char *name, UINT n) {
	UINT i, name_length;
	for (i = 0; i < JsonGetCount(object); i++) {
		name_length = StrLen(object->names[i]);
		if (name_length != n) {
			continue;
		}
		if (strncmp(object->names[i], name, n) == 0) {
			return object->values[i];
		}
	}
	return NULL;
}