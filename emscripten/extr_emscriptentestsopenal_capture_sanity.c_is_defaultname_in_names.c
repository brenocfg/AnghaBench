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
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static bool is_defaultname_in_names(const char *dft, const char *names) {
    for(const char *name = names; *name ; name += 1+strlen(name)) {
        if(!strcmp(dft, name))
            return true;
    }
    return false;
}