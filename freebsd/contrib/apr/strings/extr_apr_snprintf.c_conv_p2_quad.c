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
typedef  int apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_uint32_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int APR_UINT32_MAX ; 
 char* conv_p2 (int /*<<< orphan*/ ,int,char,char*,int*) ; 

__attribute__((used)) static char *conv_p2_quad(apr_uint64_t num, register int nbits,
                     char format, char *buf_end, register apr_size_t *len)
{
    register int mask = (1 << nbits) - 1;
    register char *p = buf_end;
    static const char low_digits[] = "0123456789abcdef";
    static const char upper_digits[] = "0123456789ABCDEF";
    register const char *digits = (format == 'X') ? upper_digits : low_digits;

    if (num <= APR_UINT32_MAX)
        return(conv_p2((apr_uint32_t)num, nbits, format, buf_end, len));

    do {
        *--p = digits[num & mask];
        num >>= nbits;
    }
    while (num);

    *len = buf_end - p;
    return (p);
}