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
 int strcmp (char*,char*) ; 

__attribute__((used)) static int
strcompare(const void *p1, const void *p2)
{
	char *s1 = *((char **)p1);
	char *s2 = *((char **)p2);

	return (strcmp(s1, s2));
}