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
 int abs (int) ; 
 int /*<<< orphan*/  reverse (char*,char*) ; 
 char* utoa (unsigned int,char*,int) ; 

char* itoa(int value, char* result, int base) {
    if(base < 2 || base > 16) {
        *result = 0;
        return result;
    }
    if (base != 10) {
	return utoa((unsigned)value, result, base);
   }

    char* out = result;
    int quotient = abs(value);

    do {
        const int tmp = quotient / base;
        *out = "0123456789abcdef"[quotient - (tmp * base)];
        ++out;
        quotient = tmp;
    } while(quotient);

    // Apply negative sign
    if(value < 0)
        *out++ = '-';

    reverse(result, out);
    *out = 0;
    return result;
}