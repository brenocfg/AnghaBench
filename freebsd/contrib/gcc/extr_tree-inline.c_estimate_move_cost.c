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
typedef  int /*<<< orphan*/  tree ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int MOVE_MAX_PIECES ; 
 int MOVE_RATIO ; 
 int int_size_in_bytes (int /*<<< orphan*/ ) ; 

int
estimate_move_cost (tree type)
{
  HOST_WIDE_INT size;

  size = int_size_in_bytes (type);

  if (size < 0 || size > MOVE_MAX_PIECES * MOVE_RATIO)
    /* Cost of a memcpy call, 3 arguments and the call.  */
    return 4;
  else
    return ((size + MOVE_MAX_PIECES - 1) / MOVE_MAX_PIECES);
}