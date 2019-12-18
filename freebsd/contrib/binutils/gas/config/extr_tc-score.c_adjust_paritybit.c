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
typedef  enum insn_class { ____Placeholder_insn_class } insn_class ;

/* Variables and functions */
 int INSN_CLASS_16 ; 
 int INSN_CLASS_32 ; 
 int INSN_CLASS_PCE ; 
 int INSN_CLASS_SYN ; 
 int /*<<< orphan*/  abort () ; 

__attribute__((used)) static unsigned long
adjust_paritybit (unsigned long m_code, enum insn_class class)
{
  unsigned long result = 0;
  unsigned long m_code_high = 0;
  unsigned long m_code_low = 0;
  unsigned long pb_high = 0;
  unsigned long pb_low = 0;

  if (class == INSN_CLASS_32)
    {
      pb_high = 0x80000000;
      pb_low = 0x00008000;
    }
  else if (class == INSN_CLASS_16)
    {
      pb_high = 0;
      pb_low = 0;
    }
  else if (class == INSN_CLASS_PCE)
    {
      pb_high = 0;
      pb_low = 0x00008000;
    }
  else if (class == INSN_CLASS_SYN)
    {
      /* FIXME.  at this time, INSN_CLASS_SYN must be 32 bit, but, instruction type should
         be changed if macro instruction has been expanded.  */
      pb_high = 0x80000000;
      pb_low = 0x00008000;
    }
  else
    {
      abort ();
    }

  m_code_high = m_code & 0x3fff8000;
  m_code_low = m_code & 0x00007fff;
  result = pb_high | (m_code_high << 1) | pb_low | m_code_low;
  return result;

}