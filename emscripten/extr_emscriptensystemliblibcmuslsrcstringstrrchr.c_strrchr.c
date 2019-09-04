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
 char* __memrchr (char const*,int,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

char *strrchr(const char *s, int c)
{
	return __memrchr(s, c, strlen(s) + 1);
}