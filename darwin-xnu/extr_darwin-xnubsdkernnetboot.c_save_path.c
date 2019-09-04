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
 scalar_t__ kalloc (int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
save_path(char * * str_p, int * length_p, char * path)
{
    *length_p = strlen(path) + 1;
    *str_p = (char *)kalloc(*length_p);
    strlcpy(*str_p, path, *length_p);
    return;
}