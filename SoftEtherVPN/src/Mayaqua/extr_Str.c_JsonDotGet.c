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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  JSON_VALUE ;
typedef  int /*<<< orphan*/  JSON_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/ * JsonGet (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * JsonValueGetObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_object_nget_value (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 

JSON_VALUE * JsonDotGet(JSON_OBJECT *object, char *name) {
	char *dot_position = strchr(name, '.');
	if (!dot_position) {
		return JsonGet(object, name);
	}
	object = JsonValueGetObject(json_object_nget_value(object, name, (UINT)(dot_position - name)));
	return JsonDotGet(object, dot_position + 1);
}