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

/* Variables and functions */
 int Util_sscanbool (char const*) ; 
 char* get_token () ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int get_bool(void)
{
	const char *t;
	t = get_token();
	if (t != NULL) {
		int result = Util_sscanbool(t);
		if (result >= 0)
			return result;
	}
	printf("Invalid argument (should be 0 or 1)!\n");
	return -1;
}