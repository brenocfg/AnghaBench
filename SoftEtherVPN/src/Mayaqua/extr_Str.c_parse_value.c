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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  JSON_VALUE ;

/* Variables and functions */
 scalar_t__ MAX_NESTING ; 
 int /*<<< orphan*/  SKIP_WHITESPACES (char**) ; 
 int /*<<< orphan*/ * parse_array_value (char**,scalar_t__) ; 
 int /*<<< orphan*/ * parse_boolean_value (char**) ; 
 int /*<<< orphan*/ * parse_null_value (char**) ; 
 int /*<<< orphan*/ * parse_number_value (char**) ; 
 int /*<<< orphan*/ * parse_object_value (char**,scalar_t__) ; 
 int /*<<< orphan*/ * parse_string_value (char**) ; 

__attribute__((used)) static JSON_VALUE * parse_value(char **string, UINT nesting) {
	if (nesting > MAX_NESTING) {
		return NULL;
	}
	SKIP_WHITESPACES(string);
	switch (**string) {
	case '{':
		return parse_object_value(string, nesting + 1);
	case '[':
		return parse_array_value(string, nesting + 1);
	case '\"':
		return parse_string_value(string);
	case 'f': case 't':
		return parse_boolean_value(string);
	case '-':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		return parse_number_value(string);
	case 'n':
		return parse_null_value(string);
	default:
		return NULL;
	}
}