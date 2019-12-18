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
typedef  int /*<<< orphan*/  export_type ;

/* Variables and functions */
 int d_nfuncs ; 

__attribute__((used)) static void
remove_null_names (export_type **ptr)
{
  int src;
  int dst;

  for (dst = src = 0; src < d_nfuncs; src++)
    {
      if (ptr[src])
	{
	  ptr[dst] = ptr[src];
	  dst++;
	}
    }
  d_nfuncs = dst;
}