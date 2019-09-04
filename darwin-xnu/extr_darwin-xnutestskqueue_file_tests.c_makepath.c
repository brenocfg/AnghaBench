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
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

void 
makepath(char *buf, const char *dir, const char *file) 
{
	strcpy(buf, dir);
	strcat(buf, "/");
	strcat(buf, file);
}