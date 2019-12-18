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
 int /*<<< orphan*/  strcat (char*,char*) ; 

int sprintf_buffer(char *s, int i)
{
	int j;
	if ( i <= 0 ) return 0;
	for ( j = 0; j < i; j++) strcat(s," ");
	return 0;
}