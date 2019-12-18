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
 int /*<<< orphan*/  NAME_CHARS ; 
 size_t strlen (char const*) ; 
 size_t strspn (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
is_valid_tube(const char *name, size_t max)
{
    size_t len = strlen(name);
    return 0 < len && len <= max &&
        strspn(name, NAME_CHARS) == len &&
        name[0] != '-';
}