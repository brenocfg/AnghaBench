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

/* Variables and functions */
 int /*<<< orphan*/  JSON_RET_ERROR ; 
 int /*<<< orphan*/  JSON_RET_OK ; 
 int /*<<< orphan*/  SKIP_CHAR (char**) ; 

__attribute__((used)) static UINT skip_quotes(char **string) {
	if (**string != '\"') {
		return JSON_RET_ERROR;
	}
	SKIP_CHAR(string);
	while (**string != '\"') {
		if (**string == '\0') {
			return JSON_RET_ERROR;
		}
		else if (**string == '\\') {
			SKIP_CHAR(string);
			if (**string == '\0') {
				return JSON_RET_ERROR;
			}
		}
		SKIP_CHAR(string);
	}
	SKIP_CHAR(string);
	return JSON_RET_OK;
}