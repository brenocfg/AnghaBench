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
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  UCH (char) ; 
 scalar_t__ isspace (int /*<<< orphan*/ ) ; 
 long strtol (char*,char**,int) ; 

__attribute__((used)) static int
decode_percent(char *buffer)
{
    char *tmp = 0;
    long value = strtol(buffer, &tmp, 10);

    if (tmp != 0 && (*tmp == 0 || isspace(UCH(*tmp))) && value >= 0) {
	return TRUE;
    }
    return FALSE;
}