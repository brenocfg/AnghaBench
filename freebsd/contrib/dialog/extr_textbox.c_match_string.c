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
typedef  int /*<<< orphan*/  MY_OBJ ;

/* Variables and functions */
 char* get_line (int /*<<< orphan*/ *) ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static bool
match_string(MY_OBJ * obj, char *string)
{
    char *match = get_line(obj);
    return strstr(match, string) != 0;
}