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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int BLKmode ; 
 unsigned long GET_MODE_SIZE (int) ; 
 scalar_t__ TARGET_32BIT ; 
 unsigned long int_size_in_bytes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long
rs6000_arg_size (enum machine_mode mode, tree type)
{
  unsigned long size;

  if (mode != BLKmode)
    size = GET_MODE_SIZE (mode);
  else
    size = int_size_in_bytes (type);

  if (TARGET_32BIT)
    return (size + 3) >> 2;
  else
    return (size + 7) >> 3;
}