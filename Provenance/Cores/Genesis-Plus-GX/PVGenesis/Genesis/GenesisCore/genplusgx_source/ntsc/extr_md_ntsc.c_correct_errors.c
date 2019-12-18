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
typedef  scalar_t__ md_ntsc_rgb_t ;

/* Variables and functions */
 int /*<<< orphan*/  CORRECT_ERROR (unsigned int) ; 
 int rgb_kernel_size ; 

__attribute__((used)) static void correct_errors( md_ntsc_rgb_t color, md_ntsc_rgb_t* out )
{
  unsigned i;
  for ( i = 0; i < rgb_kernel_size / 4; i++ )
  {
    md_ntsc_rgb_t error = color -
        out [i    ] - out [i + 2    +16] - out [i + 4    ] - out [i + 6    +16] -
        out [i + 8] - out [(i+10)%16+16] - out [(i+12)%16] - out [(i+14)%16+16];
    CORRECT_ERROR( i + 6 + 16 );
    /*DISTRIBUTE_ERROR( 2+16, 4, 6+16 );*/
  }
}