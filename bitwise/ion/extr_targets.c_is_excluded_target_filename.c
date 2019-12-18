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
 int MAX_PATH ; 
 int get_arch (char*) ; 
 int get_os (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 
 int target_arch ; 
 int target_os ; 

bool is_excluded_target_filename(const char *name) {
    const char *end = name + strlen(name);

    const char *ptr1 = end;
    while (ptr1 != name && ptr1[-1] != '_') {
        ptr1--;
    }
    char str1[MAX_PATH];
    if (ptr1 == name) {
        str1[0] = 0;
    } else {
        memcpy(str1, ptr1, end - ptr1);
        str1[end - ptr1] = 0;
        ptr1--;
    }

    const char *ptr2 = ptr1;
    while (ptr2 != name && ptr2[-1] != '_') {
        ptr2--;
    }
    char str2[MAX_PATH];
    if (ptr2 == name) {
        str2[0] = 0;
    } else {
        memcpy(str2, ptr2, ptr1 - ptr2);
        str2[ptr1 - ptr2] = 0;
    }

    int os1 = get_os(str1);
    int arch1 = get_arch(str1);
    int os2 = get_os(str2);
    int arch2 = get_arch(str2);
    if (arch1 != -1 && os2 != -1) {
        return arch1 != target_arch || os2 != target_os;
    } else if (arch2 != -1 && os1 != -1) {
        return arch2 != target_arch || os1 != target_os;
    } else if (os1 != -1) {
        return os1 != target_os;
    } else if (arch1 != -1) {
        return arch1 != target_arch;
    } else {
        return false;
    }
}