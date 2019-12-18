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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_INT (int) ; 
 int INTVAL (int /*<<< orphan*/ ) ; 

rtx
mips_prefetch_cookie (rtx write, rtx locality)
{
  /* store_streamed / load_streamed.  */
  if (INTVAL (locality) <= 0)
    return GEN_INT (INTVAL (write) + 4);

  /* store / load.  */
  if (INTVAL (locality) <= 2)
    return write;

  /* store_retained / load_retained.  */
  return GEN_INT (INTVAL (write) + 6);
}