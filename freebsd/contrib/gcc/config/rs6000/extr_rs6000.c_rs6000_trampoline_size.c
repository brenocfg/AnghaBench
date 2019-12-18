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
#define  ABI_AIX 130 
#define  ABI_DARWIN 129 
#define  ABI_V4 128 
 int DEFAULT_ABI ; 
 int /*<<< orphan*/  TARGET_32BIT ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

int
rs6000_trampoline_size (void)
{
  int ret = 0;

  switch (DEFAULT_ABI)
    {
    default:
      gcc_unreachable ();

    case ABI_AIX:
      ret = (TARGET_32BIT) ? 12 : 24;
      break;

    case ABI_DARWIN:
    case ABI_V4:
      ret = (TARGET_32BIT) ? 40 : 48;
      break;
    }

  return ret;
}