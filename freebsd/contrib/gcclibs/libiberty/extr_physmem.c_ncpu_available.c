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
typedef  int /*<<< orphan*/  ncpu ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
#define  CTL_HW 130 
#define  HW_AVAILCPU 129 
#define  HW_NCPU 128 
 scalar_t__ sysctl (int*,int /*<<< orphan*/ ,unsigned int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

unsigned int
ncpu_available (void)
{
#if HAVE_SYSCTL && defined HW_AVAILCPU
  { /* This works on *bsd and darwin.  */
    unsigned int ncpu;
    size_t len = sizeof ncpu;
    static int mib[2] = { CTL_HW, HW_AVAILCPU };

    if (sysctl (mib, ARRAY_SIZE (mib), &ncpu, &len, NULL, 0) == 0
	&& len == sizeof (ncpu))
      return ncpu;
  }
#endif
#if HAVE_SYSCTL && defined HW_NCPU
  { /* This works on *bsd and darwin.  */
    unsigned int ncpu;
    size_t len = sizeof ncpu;
    static int mib[2] = { CTL_HW, HW_NCPU };

    if (sysctl (mib, ARRAY_SIZE (mib), &ncpu, &len, NULL, 0) == 0
	&& len == sizeof (ncpu))
      return ncpu;
  }
#endif
  return 1;
}