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
typedef  int /*<<< orphan*/  j_common_ptr ;

/* Variables and functions */
 int /*<<< orphan*/  _fheapmin () ; 

void
jpeg_mem_term (j_common_ptr cinfo)
{
  /* Microsoft C, at least in v6.00A, will not successfully reclaim freed
   * blocks of size > 32Kbytes unless we give it a kick in the rear, like so:
   */
#ifdef NEED_FHEAPMIN
  _fheapmin();
#endif
}