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
 char* dlg_strclone (char const*) ; 
 int /*<<< orphan*/  dlg_tab_correct_str (char*) ; 
 int /*<<< orphan*/  dlg_trim_string (char*) ; 

__attribute__((used)) static char *
clean_copy(const char *string)
{
    char *result = dlg_strclone(string);

    dlg_trim_string(result);
    dlg_tab_correct_str(result);
    return result;
}