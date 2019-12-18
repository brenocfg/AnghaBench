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
 scalar_t__ GELF_ST_BIND (unsigned char) ; 
 scalar_t__ STB_GLOBAL ; 
 scalar_t__ STB_GNU_UNIQUE ; 

__attribute__((used)) static int
is_global_symbol(unsigned char st_info)
{

	if (GELF_ST_BIND(st_info) == STB_GLOBAL ||
	    GELF_ST_BIND(st_info) == STB_GNU_UNIQUE)
		return (1);

	return (0);
}