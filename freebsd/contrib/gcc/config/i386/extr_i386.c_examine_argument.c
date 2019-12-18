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
typedef  int /*<<< orphan*/  tree ;
typedef  enum x86_64_reg_class { ____Placeholder_x86_64_reg_class } x86_64_reg_class ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int MAX_CLASSES ; 
#define  X86_64_COMPLEX_X87_CLASS 138 
#define  X86_64_INTEGERSI_CLASS 137 
#define  X86_64_INTEGER_CLASS 136 
#define  X86_64_MEMORY_CLASS 135 
#define  X86_64_NO_CLASS 134 
#define  X86_64_SSEDF_CLASS 133 
#define  X86_64_SSESF_CLASS 132 
#define  X86_64_SSEUP_CLASS 131 
#define  X86_64_SSE_CLASS 130 
#define  X86_64_X87UP_CLASS 129 
#define  X86_64_X87_CLASS 128 
 int classify_argument (int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static int
examine_argument (enum machine_mode mode, tree type, int in_return,
		  int *int_nregs, int *sse_nregs)
{
  enum x86_64_reg_class class[MAX_CLASSES];
  int n = classify_argument (mode, type, class, 0);

  *int_nregs = 0;
  *sse_nregs = 0;
  if (!n)
    return 0;
  for (n--; n >= 0; n--)
    switch (class[n])
      {
      case X86_64_INTEGER_CLASS:
      case X86_64_INTEGERSI_CLASS:
	(*int_nregs)++;
	break;
      case X86_64_SSE_CLASS:
      case X86_64_SSESF_CLASS:
      case X86_64_SSEDF_CLASS:
	(*sse_nregs)++;
	break;
      case X86_64_NO_CLASS:
      case X86_64_SSEUP_CLASS:
	break;
      case X86_64_X87_CLASS:
      case X86_64_X87UP_CLASS:
	if (!in_return)
	  return 0;
	break;
      case X86_64_COMPLEX_X87_CLASS:
	return in_return ? 2 : 0;
      case X86_64_MEMORY_CLASS:
	gcc_unreachable ();
      }
  return 1;
}