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
struct softfilter_implementation {int dummy; } ;
typedef  int /*<<< orphan*/  softfilter_simd_mask_t ;

/* Variables and functions */
 struct softfilter_implementation const supertwoxsai_generic ; 

const struct softfilter_implementation *softfilter_get_implementation(softfilter_simd_mask_t simd)
{
   (void)simd;
   return &supertwoxsai_generic;
}