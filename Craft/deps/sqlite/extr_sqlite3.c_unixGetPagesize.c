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
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 int getpagesize () ; 
 scalar_t__ sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unixGetPagesize(void){
#if HAVE_MREMAP
  return 512;
#elif defined(_BSD_SOURCE)
  return getpagesize();
#else
  return (int)sysconf(_SC_PAGESIZE);
#endif
}