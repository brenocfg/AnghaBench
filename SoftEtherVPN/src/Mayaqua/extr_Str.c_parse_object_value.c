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
 scalar_t__ JSON_RET_ERROR ; 
 int /*<<< orphan*/  JsonFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JsonGetCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * JsonNewObject () ; 
 int /*<<< orphan*/ * JsonValueGetObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SKIP_CHAR (char**) ; 
 int /*<<< orphan*/  SKIP_WHITESPACES (char**) ; 
 char* get_quoted_string (char**) ; 
 scalar_t__ json_object_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ json_object_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * parse_value (char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parson_free (char*) ; 

__attribute__((used)) static JSON_VALUE * parse_object_value(char **string, UINT nesting) {
	JSON_VALUE *output_value = JsonNewObject(), *new_value = NULL;
	JSON_OBJECT *output_object = JsonValueGetObject(output_value);
	char *new_key = NULL;
	if (output_value == NULL || **string != '{') {
		return NULL;
	}
	SKIP_CHAR(string);
	SKIP_WHITESPACES(string);
	if (**string == '}') { /* empty object */
		SKIP_CHAR(string);
		return output_value;
	}
	while (**string != '\0') {
		new_key = get_quoted_string(string);
		if (new_key == NULL) {
			JsonFree(output_value);
			return NULL;
		}
		SKIP_WHITESPACES(string);
		if (**string != ':') {
			parson_free(new_key);
			JsonFree(output_value);
			return NULL;
		}
		SKIP_CHAR(string);
		new_value = parse_value(string, nesting);
		if (new_value == NULL) {
			parson_free(new_key);
			JsonFree(output_value);
			return NULL;
		}
		if (json_object_add(output_object, new_key, new_value) == JSON_RET_ERROR) {
			parson_free(new_key);
			JsonFree(new_value);
			JsonFree(output_value);
			return NULL;
		}
		parson_free(new_key);
		SKIP_WHITESPACES(string);
		if (**string != ',') {
			break;
		}
		SKIP_CHAR(string);
		SKIP_WHITESPACES(string);
	}
	SKIP_WHITESPACES(string);
	if (**string != '}' || /* Trim object after parsing is over */
		json_object_resize(output_object, JsonGetCount(output_object)) == JSON_RET_ERROR) {
			JsonFree(output_value);
			return NULL;
	}
	SKIP_CHAR(string);
	return output_value;
}