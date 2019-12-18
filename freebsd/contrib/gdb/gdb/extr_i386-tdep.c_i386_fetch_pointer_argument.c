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
struct type {int dummy; } ;
struct frame_info {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  I386_ESP_REGNUM ; 
 scalar_t__ get_frame_register_unsigned (struct frame_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ read_memory_unsigned_integer (scalar_t__,int) ; 

__attribute__((used)) static CORE_ADDR
i386_fetch_pointer_argument (struct frame_info *frame, int argi, 
			     struct type *type)
{
  CORE_ADDR sp = get_frame_register_unsigned  (frame, I386_ESP_REGNUM);
  return read_memory_unsigned_integer (sp + (4 * (argi + 1)), 4);
}