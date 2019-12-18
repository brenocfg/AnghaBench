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
struct frame_id {void* special_addr; void* code_addr; void* stack_addr; } ;
typedef  void* CORE_ADDR ;

/* Variables and functions */

struct frame_id
frame_id_build_special (CORE_ADDR stack_addr, CORE_ADDR code_addr,
                        CORE_ADDR special_addr)
{
  struct frame_id id;
  id.stack_addr = stack_addr;
  id.code_addr = code_addr;
  id.special_addr = special_addr;
  return id;
}