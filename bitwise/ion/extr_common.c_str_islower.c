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
 scalar_t__ isalpha (char const) ; 
 int /*<<< orphan*/  islower (char const) ; 

bool str_islower(const char *str) {
    while (*str) {
        if (isalpha(*str) && !islower(*str)) {
            return false;
        }
        str++;
    }
    return true;
}