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

/* Variables and functions */
 int /*<<< orphan*/ * JsonNewBool (int) ; 
 int /*<<< orphan*/  SIZEOF_TOKEN (char*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static JSON_VALUE * parse_boolean_value(char **string) {
	UINT true_token_size = SIZEOF_TOKEN("true");
	UINT false_token_size = SIZEOF_TOKEN("false");
	if (strncmp("true", *string, true_token_size) == 0) {
		*string += true_token_size;
		return JsonNewBool(1);
	}
	else if (strncmp("false", *string, false_token_size) == 0) {
		*string += false_token_size;
		return JsonNewBool(0);
	}
	return NULL;
}