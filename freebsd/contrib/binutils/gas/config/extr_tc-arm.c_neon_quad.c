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
typedef  enum neon_shape { ____Placeholder_neon_shape } neon_shape ;

/* Variables and functions */
 scalar_t__ SC_QUAD ; 
 scalar_t__* neon_shape_class ; 

__attribute__((used)) static int
neon_quad (enum neon_shape shape)
{
  return neon_shape_class[shape] == SC_QUAD;
}