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
 int /*<<< orphan*/  write (int,...) ; 

void outputushort(int num)
{

    static unsigned char	buff[5] = { 0, 0, 0, 0, '\n' };
    static char*		badbuff = "xxxx\n";

    // outputs a 16-bit # in hex or "xxxx" if -1.
    if (num < 0)
    {
	write(1, badbuff, 5);
    }
    else
    {
	buff[0] = num>>12;
	buff[0] += buff[0] > 9 ? 'a'-10 : '0';
	buff[1] = (num>>8) & 0xf;
	buff[1] += buff[1] > 9 ? 'a'-10 : '0';
	buff[2] = (num>>4) & 0xf;
	buff[2] += buff[2] > 9 ? 'a'-10 : '0';
	buff[3] = num & 0xf;
	buff[3] += buff[3] > 9 ? 'a'-10 : '0';
	write(1, buff, 5);
    }
}