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
 int /*<<< orphan*/  printf (char*,char) ; 

__attribute__((used)) static void do_suffix(int x) {
	static char suffixes[] = "0F234IUPVB";

	if (x < 0 || x >= (sizeof suffixes/sizeof suffixes[0]) - 1)
		printf("%d", x);
	else
		printf("%c", suffixes[x]);
}