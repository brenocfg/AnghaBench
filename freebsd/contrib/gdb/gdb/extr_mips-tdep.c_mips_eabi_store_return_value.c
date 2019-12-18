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
struct return_value_word {int reg_offset; int buf_offset; scalar_t__ len; int /*<<< orphan*/  reg; } ;
typedef  int /*<<< orphan*/  raw_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_REGISTER_BYTE (int /*<<< orphan*/ ) ; 
 int MAX_REGISTER_SIZE ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  deprecated_write_register_bytes (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  register_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_value_location (struct type*,struct return_value_word*,struct return_value_word*) ; 

__attribute__((used)) static void
mips_eabi_store_return_value (struct type *valtype, char *valbuf)
{
  char raw_buffer[MAX_REGISTER_SIZE];
  struct return_value_word lo;
  struct return_value_word hi;
  return_value_location (valtype, &hi, &lo);

  memset (raw_buffer, 0, sizeof (raw_buffer));
  memcpy (raw_buffer + lo.reg_offset, valbuf + lo.buf_offset, lo.len);
  deprecated_write_register_bytes (DEPRECATED_REGISTER_BYTE (lo.reg),
				   raw_buffer, register_size (current_gdbarch,
							      lo.reg));

  if (hi.len > 0)
    {
      memset (raw_buffer, 0, sizeof (raw_buffer));
      memcpy (raw_buffer + hi.reg_offset, valbuf + hi.buf_offset, hi.len);
      deprecated_write_register_bytes (DEPRECATED_REGISTER_BYTE (hi.reg),
				       raw_buffer,
				       register_size (current_gdbarch,
						      hi.reg));
    }
}