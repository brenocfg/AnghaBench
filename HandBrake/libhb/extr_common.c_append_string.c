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
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* realloc (char*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char * append_string(char * dst, const char * src)
{
    int dst_len = 0, src_len, len;

    if (src == NULL)
    {
        return dst;
    }

    src_len = len = strlen(src) + 1;
    if (dst != NULL)
    {
        dst_len = strlen(dst);
        len += dst_len;
    }
    char * tmp = realloc(dst, len);
    if (tmp == NULL)
    {
        // Failed to allocate required space
        return dst;
    }
    dst = tmp;
    memcpy(dst + dst_len, src, src_len);
    return dst;
}