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
typedef  int /*<<< orphan*/  JSON_ARRAY ;

/* Variables and functions */
 scalar_t__ JSON_RET_ERROR ; 
 int /*<<< orphan*/  JsonArrayGetCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JsonFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * JsonNewArray () ; 
 int /*<<< orphan*/ * JsonValueGetArray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SKIP_CHAR (char**) ; 
 int /*<<< orphan*/  SKIP_WHITESPACES (char**) ; 
 scalar_t__ json_array_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ json_array_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * parse_value (char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static JSON_VALUE * parse_array_value(char **string, UINT nesting) {
	JSON_VALUE *output_value = JsonNewArray(), *new_array_value = NULL;
	JSON_ARRAY *output_array = JsonValueGetArray(output_value);
	if (!output_value || **string != '[') {
		return NULL;
	}
	SKIP_CHAR(string);
	SKIP_WHITESPACES(string);
	if (**string == ']') { /* empty array */
		SKIP_CHAR(string);
		return output_value;
	}
	while (**string != '\0') {
		new_array_value = parse_value(string, nesting);
		if (new_array_value == NULL) {
			JsonFree(output_value);
			return NULL;
		}
		if (json_array_add(output_array, new_array_value) == JSON_RET_ERROR) {
			JsonFree(new_array_value);
			JsonFree(output_value);
			return NULL;
		}
		SKIP_WHITESPACES(string);
		if (**string != ',') {
			break;
		}
		SKIP_CHAR(string);
		SKIP_WHITESPACES(string);
	}
	SKIP_WHITESPACES(string);
	if (**string != ']' || /* Trim array after parsing is over */
		json_array_resize(output_array, JsonArrayGetCount(output_array)) == JSON_RET_ERROR) {
			JsonFree(output_value);
			return NULL;
	}
	SKIP_CHAR(string);
	return output_value;
}