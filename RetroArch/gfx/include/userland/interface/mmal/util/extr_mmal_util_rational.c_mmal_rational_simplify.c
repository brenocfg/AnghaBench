#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int num; int den; } ;
typedef  TYPE_1__ MMAL_RATIONAL_T ;

/* Variables and functions */
 int gcd (int,int) ; 

void mmal_rational_simplify(MMAL_RATIONAL_T *rational)
{
   int g = gcd(rational->num, rational->den);
   rational->num /= g;
   rational->den /= g;
}