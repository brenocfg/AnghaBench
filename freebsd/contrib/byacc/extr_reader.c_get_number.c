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
typedef  int Value_t ;

/* Variables and functions */
 int* cptr ; 
 scalar_t__ isdigit (int) ; 

__attribute__((used)) static Value_t
get_number(void)
{
    int c;
    Value_t n;

    n = 0;
    for (c = *cptr; isdigit(c); c = *++cptr)
	n = (Value_t)(10 * n + (c - '0'));

    return (n);
}