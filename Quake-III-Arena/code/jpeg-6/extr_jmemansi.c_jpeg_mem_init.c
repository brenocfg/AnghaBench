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
 long DEFAULT_MAX_MEM ; 

long
jpeg_mem_init (j_common_ptr cinfo)
{
  return DEFAULT_MAX_MEM;	/* default for max_memory_to_use */
}