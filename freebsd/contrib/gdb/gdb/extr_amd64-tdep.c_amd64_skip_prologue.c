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
struct amd64_frame_cache {scalar_t__ frameless_p; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  amd64_analyze_prologue (int /*<<< orphan*/ ,int,struct amd64_frame_cache*) ; 

__attribute__((used)) static CORE_ADDR
amd64_skip_prologue (CORE_ADDR start_pc)
{
  struct amd64_frame_cache cache;
  CORE_ADDR pc;

  pc = amd64_analyze_prologue (start_pc, 0xffffffffffffffff, &cache);
  if (cache.frameless_p)
    return start_pc;

  return pc;
}