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
typedef  int apr_size_t ;
typedef  scalar_t__ apr_int64_t ;
typedef  int /*<<< orphan*/  apr_int32_t ;

/* Variables and functions */
 scalar_t__ APR_INT32_MAX ; 
 scalar_t__ APR_INT32_MIN ; 
 int APR_UINT32_MAX ; 
 int FALSE ; 
 char* conv_10 (int /*<<< orphan*/ ,int,int*,char*,int*) ; 

__attribute__((used)) static char *conv_10_quad(apr_int64_t num, register int is_unsigned,
                     register int *is_negative, char *buf_end,
                     register apr_size_t *len)
{
    register char *p = buf_end;
    apr_uint64_t magnitude = num;

    /*
     * We see if we can use the faster non-quad version by checking the
     * number against the largest long value it can be. If <=, we
     * punt to the quicker version.
     */
    if ((magnitude <= APR_UINT32_MAX && is_unsigned)
        || (num <= APR_INT32_MAX && num >= APR_INT32_MIN && !is_unsigned))
            return(conv_10((apr_int32_t)num, is_unsigned, is_negative, buf_end, len));

    if (is_unsigned) {
        *is_negative = FALSE;
    }
    else {
        *is_negative = (num < 0);

        /*
         * On a 2's complement machine, negating the most negative integer 
         * results in a number that cannot be represented as a signed integer.
         * Here is what we do to obtain the number's magnitude:
         *      a. add 1 to the number
         *      b. negate it (becomes positive)
         *      c. convert it to unsigned
         *      d. add 1
         */
        if (*is_negative) {
            apr_int64_t t = num + 1;
            magnitude = ((apr_uint64_t) -t) + 1;
        }
    }

    /*
     * We use a do-while loop so that we write at least 1 digit 
     */
    do {
        apr_uint64_t new_magnitude = magnitude / 10;

        *--p = (char) (magnitude - new_magnitude * 10 + '0');
        magnitude = new_magnitude;
    }
    while (magnitude);

    *len = buf_end - p;
    return (p);
}