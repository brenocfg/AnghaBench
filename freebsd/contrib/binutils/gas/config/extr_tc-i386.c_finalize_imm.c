#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int* operand_types; } ;
struct TYPE_4__ {unsigned int* types; scalar_t__ suffix; scalar_t__* prefix; TYPE_1__ tm; } ;

/* Variables and functions */
 scalar_t__ BYTE_MNEM_SUFFIX ; 
 scalar_t__ CODE_16BIT ; 
 size_t DATA_PREFIX ; 
 unsigned int Imm ; 
 unsigned int Imm16 ; 
 unsigned int Imm32 ; 
 unsigned int Imm32S ; 
 unsigned int Imm64 ; 
 unsigned int Imm8 ; 
 unsigned int Imm8S ; 
 scalar_t__ QWORD_MNEM_SUFFIX ; 
 scalar_t__ WORD_MNEM_SUFFIX ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ flag_code ; 
 TYPE_2__ i ; 

__attribute__((used)) static int
finalize_imm (void)
{
  unsigned int overlap0, overlap1, overlap2;

  overlap0 = i.types[0] & i.tm.operand_types[0];
  if ((overlap0 & (Imm8 | Imm8S | Imm16 | Imm32 | Imm32S | Imm64))
      && overlap0 != Imm8 && overlap0 != Imm8S
      && overlap0 != Imm16 && overlap0 != Imm32S
      && overlap0 != Imm32 && overlap0 != Imm64)
    {
      if (i.suffix)
	{
	  overlap0 &= (i.suffix == BYTE_MNEM_SUFFIX
		       ? Imm8 | Imm8S
		       : (i.suffix == WORD_MNEM_SUFFIX
			  ? Imm16
			  : (i.suffix == QWORD_MNEM_SUFFIX
			     ? Imm64 | Imm32S
			     : Imm32)));
	}
      else if (overlap0 == (Imm16 | Imm32S | Imm32)
	       || overlap0 == (Imm16 | Imm32)
	       || overlap0 == (Imm16 | Imm32S))
	{
	  overlap0 = ((flag_code == CODE_16BIT) ^ (i.prefix[DATA_PREFIX] != 0)
		      ? Imm16 : Imm32S);
	}
      if (overlap0 != Imm8 && overlap0 != Imm8S
	  && overlap0 != Imm16 && overlap0 != Imm32S
	  && overlap0 != Imm32 && overlap0 != Imm64)
	{
	  as_bad (_("no instruction mnemonic suffix given; "
		    "can't determine immediate size"));
	  return 0;
	}
    }
  i.types[0] = overlap0;

  overlap1 = i.types[1] & i.tm.operand_types[1];
  if ((overlap1 & (Imm8 | Imm8S | Imm16 | Imm32S | Imm32 | Imm64))
      && overlap1 != Imm8 && overlap1 != Imm8S
      && overlap1 != Imm16 && overlap1 != Imm32S
      && overlap1 != Imm32 && overlap1 != Imm64)
    {
      if (i.suffix)
	{
	  overlap1 &= (i.suffix == BYTE_MNEM_SUFFIX
		       ? Imm8 | Imm8S
		       : (i.suffix == WORD_MNEM_SUFFIX
			  ? Imm16
			  : (i.suffix == QWORD_MNEM_SUFFIX
			     ? Imm64 | Imm32S
			     : Imm32)));
	}
      else if (overlap1 == (Imm16 | Imm32 | Imm32S)
	       || overlap1 == (Imm16 | Imm32)
	       || overlap1 == (Imm16 | Imm32S))
	{
	  overlap1 = ((flag_code == CODE_16BIT) ^ (i.prefix[DATA_PREFIX] != 0)
		      ? Imm16 : Imm32S);
	}
      if (overlap1 != Imm8 && overlap1 != Imm8S
	  && overlap1 != Imm16 && overlap1 != Imm32S
	  && overlap1 != Imm32 && overlap1 != Imm64)
	{
	  as_bad (_("no instruction mnemonic suffix given; "
		    "can't determine immediate size %x %c"),
		  overlap1, i.suffix);
	  return 0;
	}
    }
  i.types[1] = overlap1;

  overlap2 = i.types[2] & i.tm.operand_types[2];
  assert ((overlap2 & Imm) == 0);
  i.types[2] = overlap2;

  return 1;
}