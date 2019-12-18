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
struct dspfilter_implementation {int dummy; } ;
typedef  int /*<<< orphan*/  dspfilter_simd_mask_t ;

/* Variables and functions */
 struct dspfilter_implementation const phaser_plug ; 

const struct dspfilter_implementation *dspfilter_get_implementation(dspfilter_simd_mask_t mask)
{
   (void)mask;
   return &phaser_plug;
}