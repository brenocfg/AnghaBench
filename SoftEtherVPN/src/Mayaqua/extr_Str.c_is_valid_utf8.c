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
typedef  int UINT ;

/* Variables and functions */
 int /*<<< orphan*/  verify_utf8_sequence (unsigned char*,int*) ; 

__attribute__((used)) static int is_valid_utf8(char *string, UINT string_len) {
	int len = 0;
	char *string_end = string + string_len;
	while (string < string_end) {
		if (!verify_utf8_sequence((unsigned char*)string, &len)) {
			return 0;
		}
		string += len;
	}
	return 1;
}