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

/* Variables and functions */
 int A_DISP_PC ; 
 int A_GBR ; 
 int A_MACH ; 
 int A_MACL ; 
 int A_PR ; 
 int A_REG_N ; 
 int A_SR ; 
 int A_VBR ; 
 int /*<<< orphan*/  isalnum (char const) ; 

int parse_reg (const char *src, int *mode, int *reg)

// Ripped out of the gas asm

{
  /* We use !isalnum for the next character after the register name, to
     make sure that we won't accidentally recognize a symbol name such as
     'sram' as being a reference to the register 'sr'.  */

  if (src[0] == 'r')
    {
      if (src[1] == '1')
	{
	  if (src[2] >= '0' && src[2] <= '5' && ! isalnum (src[3]))
	    {
	      *mode = A_REG_N;
	      *reg = 10 + src[2] - '0';
	      return 3;
	    }
	}
      if (src[1] >= '0' && src[1] <= '9' && ! isalnum (src[2]))
	{
	  *mode = A_REG_N;
	  *reg = (src[1] - '0');
	  return 2;
	}
    }

  if (src[0] == 's' && src[1] == 'r' && ! isalnum (src[2]))
    {
      *mode = A_SR;
      return 2;
    }

  if (src[0] == 's' && src[1] == 'p' && ! isalnum (src[2]))
    {
      *mode = A_REG_N;
      *reg = 15;
      return 2;
    }

  if (src[0] == 'p' && src[1] == 'r' && ! isalnum (src[2]))
    {
      *mode = A_PR;
      return 2;
    }
  if (src[0] == 'p' && src[1] == 'c' && ! isalnum (src[2]))
    {
      *mode = A_DISP_PC;
      return 2;
    }
  if (src[0] == 'g' && src[1] == 'b' && src[2] == 'r' && ! isalnum (src[3]))
    {
      *mode = A_GBR;
      return 3;
    }
  if (src[0] == 'v' && src[1] == 'b' && src[2] == 'r' && ! isalnum (src[3]))
    {
      *mode = A_VBR;
      return 3;
    }

  if (src[0] == 'm' && src[1] == 'a' && src[2] == 'c' && ! isalnum (src[4]))
    {
      if (src[3] == 'l')
	{
	  *mode = A_MACL;
	  return 4;
	}
      if (src[3] == 'h')
	{
	  *mode = A_MACH;
	  return 4;
	}
    }

  return 0;
}