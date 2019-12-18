#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ valueT ;
typedef  scalar_t__ offsetT ;
struct TYPE_11__ {scalar_t__ X_op; scalar_t__ X_add_number; } ;
struct TYPE_10__ {int fr_literal; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; int /*<<< orphan*/  base_opcode; } ;
struct TYPE_9__ {scalar_t__ prefixes; TYPE_2__* op; TYPE_1__ tm; int /*<<< orphan*/ * reloc; int /*<<< orphan*/ * prefix; } ;
struct TYPE_8__ {TYPE_6__* imms; } ;

/* Variables and functions */
 int CODE16 ; 
 scalar_t__ CODE_16BIT ; 
 size_t DATA_PREFIX ; 
 int /*<<< orphan*/  DATA_PREFIX_OPCODE ; 
 scalar_t__ O_constant ; 
 size_t REX_PREFIX ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fits_in_signed_word (scalar_t__) ; 
 int /*<<< orphan*/  fits_in_unsigned_word (scalar_t__) ; 
 int /*<<< orphan*/  fix_new_exp (TYPE_4__*,char*,int,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ flag_code ; 
 char* frag_more (int) ; 
 TYPE_4__* frag_now ; 
 TYPE_3__ i ; 
 int /*<<< orphan*/  intel_syntax ; 
 int /*<<< orphan*/  md_number_to_chars (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  reloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
output_interseg_jump (void)
{
  char *p;
  int size;
  int prefix;
  int code16;

  code16 = 0;
  if (flag_code == CODE_16BIT)
    code16 = CODE16;

  prefix = 0;
  if (i.prefix[DATA_PREFIX] != 0)
    {
      prefix = 1;
      i.prefixes -= 1;
      code16 ^= CODE16;
    }
  if (i.prefix[REX_PREFIX] != 0)
    {
      prefix++;
      i.prefixes -= 1;
    }

  size = 4;
  if (code16)
    size = 2;

  if (i.prefixes != 0 && !intel_syntax)
    as_warn (_("skipping prefixes on this instruction"));

  /* 1 opcode; 2 segment; offset  */
  p = frag_more (prefix + 1 + 2 + size);

  if (i.prefix[DATA_PREFIX] != 0)
    *p++ = DATA_PREFIX_OPCODE;

  if (i.prefix[REX_PREFIX] != 0)
    *p++ = i.prefix[REX_PREFIX];

  *p++ = i.tm.base_opcode;
  if (i.op[1].imms->X_op == O_constant)
    {
      offsetT n = i.op[1].imms->X_add_number;

      if (size == 2
	  && !fits_in_unsigned_word (n)
	  && !fits_in_signed_word (n))
	{
	  as_bad (_("16-bit jump out of range"));
	  return;
	}
      md_number_to_chars (p, n, size);
    }
  else
    fix_new_exp (frag_now, p - frag_now->fr_literal, size,
		 i.op[1].imms, 0, reloc (size, 0, 0, i.reloc[1]));
  if (i.op[0].imms->X_op != O_constant)
    as_bad (_("can't handle non absolute segment in `%s'"),
	    i.tm.name);
  md_number_to_chars (p + size, (valueT) i.op[0].imms->X_add_number, 2);
}