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
typedef  int /*<<< orphan*/  user_addr_t ;

/* Variables and functions */
 scalar_t__ copyin (int /*<<< orphan*/ ,void*,int) ; 

int fuibyte(user_addr_t addr)
{
	unsigned char byte;

	if (copyin(addr, (void *) &(byte), sizeof(char)))
		return(-1);
	return(byte);
}