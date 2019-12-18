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
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static int is_decimal(char *string, UINT length) {
	if (length > 1 && string[0] == '0' && string[1] != '.') {
		return 0;
	}
	if (length > 2 && !strncmp(string, "-0", 2) && string[2] != '.') {
		return 0;
	}
	while (length--) {
		if (strchr("xX", string[length])) {
			return 0;
		}
	}
	return 1;
}