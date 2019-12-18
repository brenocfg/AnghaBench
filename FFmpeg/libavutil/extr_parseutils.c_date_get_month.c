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
 int /*<<< orphan*/  av_strncasecmp (char const*,char const*,int) ; 
 char const** months ; 
 int strlen (char const*) ; 

__attribute__((used)) static int date_get_month(const char **pp) {
    int i = 0;
    for (; i < 12; i++) {
        if (!av_strncasecmp(*pp, months[i], 3)) {
            const char *mo_full = months[i] + 3;
            int len = strlen(mo_full);
            *pp += 3;
            if (len > 0 && !av_strncasecmp(*pp, mo_full, len))
                *pp += len;
            return i;
        }
    }
    return -1;
}