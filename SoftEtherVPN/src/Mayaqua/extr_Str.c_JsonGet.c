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
typedef  int /*<<< orphan*/  JSON_VALUE ;
typedef  int /*<<< orphan*/  JSON_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  StrLen (char*) ; 
 int /*<<< orphan*/ * json_object_nget_value (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

JSON_VALUE * JsonGet(JSON_OBJECT *object, char *name) {
	if (object == NULL || name == NULL) {
		return NULL;
	}
	return json_object_nget_value(object, name, StrLen(name));
}