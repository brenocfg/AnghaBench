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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

__attribute__((used)) static ssize_t get_string(char *buf, const char *data, int length)
{
	int i;
	memcpy(buf, data, length);

	for (i = length; i--;) {
		char c = buf[i];

		if ((c != 0) && (c != ' '))
			break;
	}

	buf[i + 1] = '\n';
	return i + 2;
}