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
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

void supcon_putc( unsigned char c )
{
	char buffer[2];
		 buffer[0] = c;
		 buffer[1] = 0;

	fputs((const char *)buffer,stdout);
}