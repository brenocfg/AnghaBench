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

void handle_symbol(char *str, int n)
{
	while (str[n] < '0' || (str[n] > '9' && str[n] < 'A') || (str[n] > 'Z' && str[n] < 'a') || str[n] > 'z')
	{
		str[n] = '\0';
		n--;
	}

	while (str[0] < '0' || (str[0] > '9' && str[0] < 'A') || (str[0] > 'Z' && str[0] < 'a') || str[0] > 'z')
	{
		int i = 0;
		while (i < n)
		{
			str[i] = str[i+1];
			i++;
		}
		str[i] = '\0';
		n--;
	}
}