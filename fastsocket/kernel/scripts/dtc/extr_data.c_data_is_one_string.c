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
struct data {int len; char* val; } ;

/* Variables and functions */

int data_is_one_string(struct data d)
{
	int i;
	int len = d.len;

	if (len == 0)
		return 0;

	for (i = 0; i < len-1; i++)
		if (d.val[i] == '\0')
			return 0;

	if (d.val[len-1] != '\0')
		return 0;

	return 1;
}