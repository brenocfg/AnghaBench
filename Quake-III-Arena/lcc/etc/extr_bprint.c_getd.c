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
 int EOF ; 
 int /*<<< orphan*/  fp ; 
 int getc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int getd(void) {
	int c, n = 0;

	while ((c = getc(fp)) != EOF && (c == ' ' || c == '\n' || c == '\t'))
		;
	if (c >= '0' && c <= '9') {
		do
			n = 10*n + (c - '0');
		while ((c = getc(fp)) >= '0' && c <= '9');
		return n;
	}
	return -1;
}