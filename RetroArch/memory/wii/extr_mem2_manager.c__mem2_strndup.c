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
 char* _mem2_calloc (int,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

char *_mem2_strndup(const char *s, size_t n)
{
    char *ptr = NULL;

    if (s)
    {
        int len = n + 1;
        ptr = _mem2_calloc(1, len);

        if (ptr)
            memcpy(ptr, s, len);
    }
    return ptr;
}