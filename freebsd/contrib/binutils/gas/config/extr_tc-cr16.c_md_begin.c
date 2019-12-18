#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* mnemonic; } ;

/* Variables and functions */
 int /*<<< orphan*/  NUMPREGPS ; 
 int /*<<< orphan*/  NUMPREGS ; 
 int /*<<< orphan*/  NUMREGPS ; 
 int /*<<< orphan*/  NUMREGS ; 
 char const* _ (char*) ; 
 int /*<<< orphan*/  as_fatal (char const*,...) ; 
 int /*<<< orphan*/ * cr16_inst_hash ; 
 TYPE_1__* cr16_instruction ; 
 int /*<<< orphan*/  cr16_pregptab ; 
 int /*<<< orphan*/  cr16_pregtab ; 
 int /*<<< orphan*/  cr16_regptab ; 
 int /*<<< orphan*/  cr16_regtab ; 
 char* hash_insert (int /*<<< orphan*/ *,char const*,char*) ; 
 int /*<<< orphan*/ * hash_new () ; 
 int /*<<< orphan*/  initialise_reg_hash_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int linkrelax ; 
 int /*<<< orphan*/  preg_hash ; 
 int /*<<< orphan*/  pregp_hash ; 
 int /*<<< orphan*/  reg_hash ; 
 int /*<<< orphan*/  regp_hash ; 
 scalar_t__ streq (char*,char const*) ; 

void
md_begin (void)
{
  int i = 0;

  /* Set up a hash table for the instructions.  */
  if ((cr16_inst_hash = hash_new ()) == NULL)
    as_fatal (_("Virtual memory exhausted"));

  while (cr16_instruction[i].mnemonic != NULL)
    {
      const char *hashret;
      const char *mnemonic = cr16_instruction[i].mnemonic;

      hashret = hash_insert (cr16_inst_hash, mnemonic,
			     (char *)(cr16_instruction + i));

      if (hashret != NULL && *hashret != '\0')
        as_fatal (_("Can't hash `%s': %s\n"), cr16_instruction[i].mnemonic,
                  *hashret == 0 ? _("(unknown reason)") : hashret);

      /* Insert unique names into hash table.  The CR16 instruction set
         has many identical opcode names that have different opcodes based
         on the operands.  This hash table then provides a quick index to
         the first opcode with a particular name in the opcode table.  */
      do
        {
          ++i;
        }
      while (cr16_instruction[i].mnemonic != NULL
             && streq (cr16_instruction[i].mnemonic, mnemonic));
    }

  /* Initialize reg_hash hash table.  */
  initialise_reg_hash_table (& reg_hash, cr16_regtab, NUMREGS);
  /* Initialize regp_hash hash table.  */
  initialise_reg_hash_table (& regp_hash, cr16_regptab, NUMREGPS);
  /* Initialize preg_hash hash table.  */
  initialise_reg_hash_table (& preg_hash, cr16_pregtab, NUMPREGS);
  /* Initialize pregp_hash hash table.  */
  initialise_reg_hash_table (& pregp_hash, cr16_pregptab, NUMPREGPS);

  /*  Set linkrelax here to avoid fixups in most sections.  */
  linkrelax = 1;
}