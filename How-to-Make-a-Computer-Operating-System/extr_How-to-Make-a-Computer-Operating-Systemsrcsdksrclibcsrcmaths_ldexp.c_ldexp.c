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
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  finite (double) ; 
 double scalbn (double,int) ; 

double ldexp( double value, int exp ) {
    if ( !finite(value) || value == 0.0 ) return value;
    value = scalbn(value,exp);
    if ( !finite(value) || value == 0.0 ) errno = ERANGE;
    return value;
}