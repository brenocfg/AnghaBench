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
struct return_value_word {int buf_offset; int reg_offset; scalar_t__ len; scalar_t__ reg; } ;

/* Variables and functions */
 int DEPRECATED_REGISTER_BYTE (scalar_t__) ; 
 scalar_t__ NUM_REGS ; 
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  return_value_location (struct type*,struct return_value_word*,struct return_value_word*) ; 

__attribute__((used)) static void
mips_eabi_extract_return_value (struct type *valtype,
				char regbuf[], char *valbuf)
{
  struct return_value_word lo;
  struct return_value_word hi;
  return_value_location (valtype, &hi, &lo);

  memcpy (valbuf + lo.buf_offset,
	  regbuf + DEPRECATED_REGISTER_BYTE (NUM_REGS + lo.reg) +
	  lo.reg_offset, lo.len);

  if (hi.len > 0)
    memcpy (valbuf + hi.buf_offset,
	    regbuf + DEPRECATED_REGISTER_BYTE (NUM_REGS + hi.reg) +
	    hi.reg_offset, hi.len);
}