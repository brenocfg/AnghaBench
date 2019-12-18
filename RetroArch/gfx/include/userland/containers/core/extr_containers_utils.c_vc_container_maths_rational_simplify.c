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
typedef  int int64_t ;

/* Variables and functions */
 int vc_container_maths_gcd (int,int) ; 

void vc_container_maths_rational_simplify(uint32_t *num, uint32_t *den)
{
   int64_t div = vc_container_maths_gcd((int64_t)*num, (int64_t)*den);
   if(div)
   {
      *num /= div;
      *den /= div;
   }
}