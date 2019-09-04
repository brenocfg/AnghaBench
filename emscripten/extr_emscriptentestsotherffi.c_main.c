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
 float add_f (float,float) ; 
 long long add_ll (long long,long long) ; 
 float import_f (float) ; 
 long long import_ll (long long) ; 

int main () {
    float a = 1.2,
          b = import_f((float)3.4),
          c;
    c = add_f(a, b);

    long long d = 1,
              e = import_ll((long long)2),
              f;
    f = add_ll(d, e);
}