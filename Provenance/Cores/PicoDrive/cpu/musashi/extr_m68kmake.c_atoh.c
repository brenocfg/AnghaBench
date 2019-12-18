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

int atoh(char* buff)
{
	int accum = 0;

	for(;;buff++)
	{
		if(*buff >= '0' && *buff <= '9')
		{
			accum <<= 4;
			accum += *buff - '0';
		}
		else if(*buff >= 'a' && *buff <= 'f')
		{
			accum <<= 4;
			accum += *buff - 'a' + 10;
		}
		else break;
	}
	return accum;
}