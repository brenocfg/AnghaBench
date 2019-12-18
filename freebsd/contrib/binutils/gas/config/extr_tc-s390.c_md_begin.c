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
struct s390_opcode {scalar_t__ min_cpu; int /*<<< orphan*/  name; } ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  PTR ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ S390_OPCODE_Z900 ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  as_warn (char*) ; 
 int /*<<< orphan*/  bfd_set_private_flags (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bss_section ; 
 scalar_t__ current_cpu ; 
 int /*<<< orphan*/  data_section ; 
 char* hash_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_new () ; 
 int /*<<< orphan*/  record_alignment (int /*<<< orphan*/ ,int) ; 
 int s390_arch_size ; 
 int s390_cie_data_alignment ; 
 scalar_t__ s390_flags ; 
 int s390_num_opcodes ; 
 int s390_num_opformats ; 
 int /*<<< orphan*/  s390_opcode_hash ; 
 struct s390_opcode* s390_opcodes ; 
 int /*<<< orphan*/  s390_opformat_hash ; 
 struct s390_opcode* s390_opformats ; 
 int /*<<< orphan*/  stdoutput ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  text_section ; 

void
md_begin ()
{
  register const struct s390_opcode *op;
  const struct s390_opcode *op_end;
  bfd_boolean dup_insn = FALSE;
  const char *retval;

  /* Give a warning if the combination -m64-bit and -Aesa is used.  */
  if (s390_arch_size == 64 && current_cpu < S390_OPCODE_Z900)
    as_warn ("The 64 bit file format is used without esame instructions.");

  s390_cie_data_alignment = -s390_arch_size / 8;

  /* Set the ELF flags if desired.  */
  if (s390_flags)
    bfd_set_private_flags (stdoutput, s390_flags);

  /* Insert the opcode formats into a hash table.  */
  s390_opformat_hash = hash_new ();

  op_end = s390_opformats + s390_num_opformats;
  for (op = s390_opformats; op < op_end; op++)
    {
      retval = hash_insert (s390_opformat_hash, op->name, (PTR) op);
      if (retval != (const char *) NULL)
	{
	  as_bad (_("Internal assembler error for instruction format %s"),
		  op->name);
	  dup_insn = TRUE;
	}
    }

  /* Insert the opcodes into a hash table.  */
  s390_opcode_hash = hash_new ();

  op_end = s390_opcodes + s390_num_opcodes;
  for (op = s390_opcodes; op < op_end; op++)
    if (op->min_cpu <= current_cpu)
      {
	retval = hash_insert (s390_opcode_hash, op->name, (PTR) op);
	if (retval != (const char *) NULL)
	  {
	    as_bad (_("Internal assembler error for instruction %s"),
		    op->name);
	    dup_insn = TRUE;
	  }
	while (op < op_end - 1 && strcmp (op->name, op[1].name) == 0)
	  op++;
      }

  if (dup_insn)
    abort ();

  record_alignment (text_section, 2);
  record_alignment (data_section, 2);
  record_alignment (bss_section, 2);

}