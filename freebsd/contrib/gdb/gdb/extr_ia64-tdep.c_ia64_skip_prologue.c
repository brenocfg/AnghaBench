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
struct ia64_frame_cache {scalar_t__ bsp; scalar_t__ cfm; scalar_t__ after_prologue; scalar_t__ base; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ examine_prologue (scalar_t__,scalar_t__,int /*<<< orphan*/ ,struct ia64_frame_cache*) ; 

CORE_ADDR
ia64_skip_prologue (CORE_ADDR pc)
{
  struct ia64_frame_cache cache;
  cache.base = 0;
  cache.after_prologue = 0;
  cache.cfm = 0;
  cache.bsp = 0;

  /* Call examine_prologue with - as third argument since we don't have a next frame pointer to send.  */
  return examine_prologue (pc, pc+1024, 0, &cache);
}