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

/* Variables and functions */
 scalar_t__ BFD_ENDIAN_BIG ; 
 char* REGISTER_NAME (int) ; 
 scalar_t__ TARGET_BYTE_ORDER ; 
 char* alloca (int) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  error (char*,int,char*) ; 
 int /*<<< orphan*/  frame_register_read (struct frame_info*,int,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int register_size (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mips_read_fp_register_single (struct frame_info *frame, int regno,
			      char *rare_buffer)
{
  int raw_size = register_size (current_gdbarch, regno);
  char *raw_buffer = alloca (raw_size);

  if (!frame_register_read (frame, regno, raw_buffer))
    error ("can't read register %d (%s)", regno, REGISTER_NAME (regno));
  if (raw_size == 8)
    {
      /* We have a 64-bit value for this register.  Find the low-order
         32 bits.  */
      int offset;

      if (TARGET_BYTE_ORDER == BFD_ENDIAN_BIG)
	offset = 4;
      else
	offset = 0;

      memcpy (rare_buffer, raw_buffer + offset, 4);
    }
  else
    {
      memcpy (rare_buffer, raw_buffer, 4);
    }
}