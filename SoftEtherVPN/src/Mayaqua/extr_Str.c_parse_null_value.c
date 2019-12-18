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
 int /*<<< orphan*/ * JsonNewNull () ; 
 int /*<<< orphan*/  SIZEOF_TOKEN (char*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static JSON_VALUE * parse_null_value(char **string) {
	UINT token_size = SIZEOF_TOKEN("null");
	if (strncmp("null", *string, token_size) == 0) {
		*string += token_size;
		return JsonNewNull();
	}
	return NULL;
}