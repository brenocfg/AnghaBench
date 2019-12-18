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

/* Variables and functions */
 scalar_t__ JSON_RET_OK ; 
 char* process_string (char*,scalar_t__) ; 
 scalar_t__ skip_quotes (char**) ; 

__attribute__((used)) static char * get_quoted_string(char **string) {
	char *string_start = *string;
	UINT string_len = 0;
	UINT status = skip_quotes(string);
	if (status != JSON_RET_OK) {
		return NULL;
	}
	string_len = (UINT)(*string - string_start - 2); /* length without quotes */
	return process_string(string_start + 1, string_len);
}