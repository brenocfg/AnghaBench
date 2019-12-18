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
struct nubus_dirent {int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 unsigned char* nubus_dirptr (struct nubus_dirent const*) ; 
 int /*<<< orphan*/  nubus_get_rom (unsigned char**,int,int /*<<< orphan*/ ) ; 

void nubus_get_rsrc_mem(void *dest, const struct nubus_dirent* dirent,
			int len)
{
	unsigned char *t = (unsigned char *)dest;
	unsigned char *p = nubus_dirptr(dirent);
	while(len)
	{
		*t++ = nubus_get_rom(&p, 1, dirent->mask);
		len--;
	}
}