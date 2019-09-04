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
 int /*<<< orphan*/  av_free (void*) ; 
 char* av_malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

__attribute__((used)) static int convert_str(void *dest, const char *buf, int len)
{
    char *str = av_malloc(len + 1);
    if (str) {
        memcpy(str, buf, len);
        str[len] = 0;
        if (*(void **)dest)
            av_free(*(void **)dest);
        *(char **)dest = str;
    }
    return !str;
}