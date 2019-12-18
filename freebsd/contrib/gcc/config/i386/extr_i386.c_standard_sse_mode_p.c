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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
#define  V16QImode 133 
#define  V2DFmode 132 
#define  V2DImode 131 
#define  V4SFmode 130 
#define  V4SImode 129 
#define  V8HImode 128 

__attribute__((used)) static int
standard_sse_mode_p (enum machine_mode mode)
{
  switch (mode)
    {
    case V16QImode:
    case V8HImode:
    case V4SImode:
    case V2DImode:
    case V4SFmode:
    case V2DFmode:
      return 1;

    default:
      return 0;
    }
}