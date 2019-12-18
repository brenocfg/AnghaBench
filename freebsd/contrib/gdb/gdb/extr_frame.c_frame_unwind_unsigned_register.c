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
struct frame_info {int dummy; } ;
typedef  int /*<<< orphan*/  ULONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_REGISTER_VIRTUAL_SIZE (int) ; 
 int MAX_REGISTER_SIZE ; 
 int /*<<< orphan*/  extract_unsigned_integer (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_unwind_register (struct frame_info*,int,char*) ; 

void
frame_unwind_unsigned_register (struct frame_info *frame, int regnum,
				ULONGEST *val)
{
  char buf[MAX_REGISTER_SIZE];
  frame_unwind_register (frame, regnum, buf);
  (*val) = extract_unsigned_integer (buf, DEPRECATED_REGISTER_VIRTUAL_SIZE (regnum));
}