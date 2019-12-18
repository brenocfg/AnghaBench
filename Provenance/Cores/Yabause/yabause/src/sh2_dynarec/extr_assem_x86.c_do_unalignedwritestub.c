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
 int /*<<< orphan*/  emit_jmp (int /*<<< orphan*/ ) ; 
 scalar_t__ out ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  set_jump_target (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ ** stubs ; 

do_unalignedwritestub(int n)
{
  set_jump_target(stubs[n][1],(int)out);
  output_byte(0xCC);
  emit_jmp(stubs[n][2]); // return address
}