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
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int,char const*) ; 

__attribute__((used)) static char *
bitvector_process(char *p, u64 vector)
{
	int i,j;
	const char *units[]={ "", "K", "M", "G", "T" };

	for (i=0, j=0; i < 64; i++ , j=i/10) {
		if (vector & 0x1) {
			p += sprintf(p, "%d%s ", 1 << (i-j*10), units[j]);
		}
		vector >>= 1;
	}
	return p;
}