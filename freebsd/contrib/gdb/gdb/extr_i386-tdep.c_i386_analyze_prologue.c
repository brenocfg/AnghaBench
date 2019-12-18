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
struct i386_frame_cache {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  i386_analyze_frame_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct i386_frame_cache*) ; 
 int /*<<< orphan*/  i386_analyze_register_saves (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct i386_frame_cache*) ; 
 int /*<<< orphan*/  i386_analyze_struct_return (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct i386_frame_cache*) ; 
 int /*<<< orphan*/  i386_follow_jump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i386_skip_probe (int /*<<< orphan*/ ) ; 

__attribute__((used)) static CORE_ADDR
i386_analyze_prologue (CORE_ADDR pc, CORE_ADDR current_pc,
		       struct i386_frame_cache *cache)
{
  pc = i386_follow_jump (pc);
  pc = i386_analyze_struct_return (pc, current_pc, cache);
  pc = i386_skip_probe (pc);
  pc = i386_analyze_frame_setup (pc, current_pc, cache);
  return i386_analyze_register_saves (pc, current_pc, cache);
}