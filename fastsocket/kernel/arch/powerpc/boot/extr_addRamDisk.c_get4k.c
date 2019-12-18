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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned int fread (char*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get4k(FILE *file, char *buf )
{
	unsigned j;
	unsigned num = fread(buf, 1, 4096, file);
	for ( j=num; j<4096; ++j )
		buf[j] = 0;
}