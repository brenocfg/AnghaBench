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
typedef  int offsetT ;

/* Variables and functions */
 int Cpu186 ; 
 int Cpu286 ; 
 int Cpu386 ; 
 int Cpu486 ; 
 int CpuNo64 ; 
 unsigned int Imm1 ; 
 unsigned int Imm16 ; 
 unsigned int Imm32 ; 
 unsigned int Imm32S ; 
 unsigned int Imm64 ; 
 unsigned int Imm8 ; 
 unsigned int Imm8S ; 
 int cpu_arch_flags ; 
 scalar_t__ fits_in_signed_byte (int) ; 
 scalar_t__ fits_in_signed_long (int) ; 
 scalar_t__ fits_in_signed_word (int) ; 
 scalar_t__ fits_in_unsigned_byte (int) ; 
 scalar_t__ fits_in_unsigned_long (int) ; 
 scalar_t__ fits_in_unsigned_word (int) ; 

__attribute__((used)) static unsigned int
smallest_imm_type (offsetT num)
{
  if (cpu_arch_flags != (Cpu186 | Cpu286 | Cpu386 | Cpu486 | CpuNo64))
    {
      /* This code is disabled on the 486 because all the Imm1 forms
	 in the opcode table are slower on the i486.  They're the
	 versions with the implicitly specified single-position
	 displacement, which has another syntax if you really want to
	 use that form.  */
      if (num == 1)
	return Imm1 | Imm8 | Imm8S | Imm16 | Imm32 | Imm32S | Imm64;
    }
  return (fits_in_signed_byte (num)
	  ? (Imm8S | Imm8 | Imm16 | Imm32 | Imm32S | Imm64)
	  : fits_in_unsigned_byte (num)
	  ? (Imm8 | Imm16 | Imm32 | Imm32S | Imm64)
	  : (fits_in_signed_word (num) || fits_in_unsigned_word (num))
	  ? (Imm16 | Imm32 | Imm32S | Imm64)
	  : fits_in_signed_long (num)
	  ? (Imm32 | Imm32S | Imm64)
	  : fits_in_unsigned_long (num)
	  ? (Imm32 | Imm64)
	  : Imm64);
}