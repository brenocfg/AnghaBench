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
 char* gdb_cris_memchr (char*,char,int) ; 
 char* hex_asc ; 

__attribute__((used)) static int
gdb_cris_strtol(const char *s, char **endptr, int base)
{
	char *s1;
	char *sd;
	int x = 0;

	for (s1 = (char*)s; (sd = gdb_cris_memchr(hex_asc, *s1, base)) != NULL; ++s1)
		x = x * base + (sd - hex_asc);

        if (endptr) {
                /* Unconverted suffix is stored in endptr unless endptr is NULL. */
                *endptr = s1;
        }

	return x;
}