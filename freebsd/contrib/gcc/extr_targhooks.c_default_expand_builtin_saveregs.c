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
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  error (char*) ; 

rtx
default_expand_builtin_saveregs (void)
{
  error ("__builtin_saveregs not supported by this target");
  return const0_rtx;
}