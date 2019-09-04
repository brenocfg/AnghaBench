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
struct substring {char* string; size_t length; } ;

/* Variables and functions */

__attribute__((used)) static struct substring
necp_trim_dots_and_stars(char *string, size_t length)
{
	struct substring sub;
	sub.string = string;
	sub.length = string ? length : 0;

	while (sub.length && (sub.string[0] == '.' || sub.string[0] == '*')) {
		sub.string++;
		sub.length--;
	}

	while (sub.length && (sub.string[sub.length - 1] == '.' || sub.string[sub.length - 1] == '*')) {
		sub.length--;
	}

	return (sub);
}