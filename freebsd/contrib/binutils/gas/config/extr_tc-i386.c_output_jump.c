#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int fx_signed; } ;
typedef  TYPE_3__ fixS ;
struct TYPE_12__ {int fr_literal; } ;
struct TYPE_8__ {int opcode_modifier; int /*<<< orphan*/  base_opcode; } ;
struct TYPE_11__ {scalar_t__* prefix; scalar_t__ prefixes; int /*<<< orphan*/ * reloc; TYPE_2__* op; TYPE_1__ tm; } ;
struct TYPE_9__ {int /*<<< orphan*/  disps; } ;

/* Variables and functions */
 size_t ADDR_PREFIX ; 
 scalar_t__ ADDR_PREFIX_OPCODE ; 
 int CODE16 ; 
 scalar_t__ CODE_16BIT ; 
 scalar_t__ CS_PREFIX_OPCODE ; 
 size_t DATA_PREFIX ; 
 scalar_t__ DATA_PREFIX_OPCODE ; 
 scalar_t__ DS_PREFIX_OPCODE ; 
 int /*<<< orphan*/  FRAG_APPEND_1_CHAR (scalar_t__) ; 
 int JumpByte ; 
 size_t REX_PREFIX ; 
 size_t SEG_PREFIX ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ) ; 
 TYPE_3__* fix_new_exp (TYPE_5__*,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ flag_code ; 
 char* frag_more (int) ; 
 TYPE_5__* frag_now ; 
 TYPE_4__ i ; 
 int /*<<< orphan*/  intel_syntax ; 
 int /*<<< orphan*/  reloc (int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
output_jump (void)
{
  char *p;
  int size;
  fixS *fixP;

  if (i.tm.opcode_modifier & JumpByte)
    {
      /* This is a loop or jecxz type instruction.  */
      size = 1;
      if (i.prefix[ADDR_PREFIX] != 0)
	{
	  FRAG_APPEND_1_CHAR (ADDR_PREFIX_OPCODE);
	  i.prefixes -= 1;
	}
      /* Pentium4 branch hints.  */
      if (i.prefix[SEG_PREFIX] == CS_PREFIX_OPCODE /* not taken */
	  || i.prefix[SEG_PREFIX] == DS_PREFIX_OPCODE /* taken */)
	{
	  FRAG_APPEND_1_CHAR (i.prefix[SEG_PREFIX]);
	  i.prefixes--;
	}
    }
  else
    {
      int code16;

      code16 = 0;
      if (flag_code == CODE_16BIT)
	code16 = CODE16;

      if (i.prefix[DATA_PREFIX] != 0)
	{
	  FRAG_APPEND_1_CHAR (DATA_PREFIX_OPCODE);
	  i.prefixes -= 1;
	  code16 ^= CODE16;
	}

      size = 4;
      if (code16)
	size = 2;
    }

  if (i.prefix[REX_PREFIX] != 0)
    {
      FRAG_APPEND_1_CHAR (i.prefix[REX_PREFIX]);
      i.prefixes -= 1;
    }

  if (i.prefixes != 0 && !intel_syntax)
    as_warn (_("skipping prefixes on this instruction"));

  p = frag_more (1 + size);
  *p++ = i.tm.base_opcode;

  fixP = fix_new_exp (frag_now, p - frag_now->fr_literal, size,
		      i.op[0].disps, 1, reloc (size, 1, 1, i.reloc[0]));

  /* All jumps handled here are signed, but don't use a signed limit
     check for 32 and 16 bit jumps as we want to allow wrap around at
     4G and 64k respectively.  */
  if (size == 1)
    fixP->fx_signed = 1;
}