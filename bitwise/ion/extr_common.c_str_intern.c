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
 char const* str_intern_range (char const*,char const*) ; 
 int strlen (char const*) ; 

const char *str_intern(const char *str) {
    return str_intern_range(str, str + strlen(str));
}