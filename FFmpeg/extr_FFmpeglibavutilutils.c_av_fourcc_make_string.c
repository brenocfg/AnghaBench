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
typedef  int uint32_t ;

/* Variables and functions */
 size_t AV_FOURCC_MAX_STRING_SIZE ; 
 int snprintf (char*,size_t,char*,int const) ; 
 scalar_t__ strchr (char*,int const) ; 

char *av_fourcc_make_string(char *buf, uint32_t fourcc)
{
    int i;
    char *orig_buf = buf;
    size_t buf_size = AV_FOURCC_MAX_STRING_SIZE;

    for (i = 0; i < 4; i++) {
        const int c = fourcc & 0xff;
        const int print_chr = (c >= '0' && c <= '9') ||
                              (c >= 'a' && c <= 'z') ||
                              (c >= 'A' && c <= 'Z') ||
                              (c && strchr(". -_", c));
        const int len = snprintf(buf, buf_size, print_chr ? "%c" : "[%d]", c);
        if (len < 0)
            break;
        buf += len;
        buf_size = buf_size > len ? buf_size - len : 0;
        fourcc >>= 8;
    }

    return orig_buf;
}