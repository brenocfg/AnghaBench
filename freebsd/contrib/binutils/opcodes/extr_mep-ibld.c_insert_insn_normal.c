#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_vma ;
struct TYPE_7__ {char* (* insert_operand ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ base_insn_bitsize; } ;
typedef  scalar_t__ CGEN_SYNTAX_CHAR_TYPE ;
typedef  int /*<<< orphan*/  CGEN_SYNTAX ;
typedef  int /*<<< orphan*/  CGEN_INSN_BYTES_PTR ;
typedef  int /*<<< orphan*/  CGEN_INSN ;
typedef  int /*<<< orphan*/  CGEN_FIELDS ;
typedef  TYPE_1__* CGEN_CPU_DESC ;

/* Variables and functions */
 scalar_t__ CGEN_FIELDS_BITSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CGEN_INIT_INSERT (TYPE_1__*) ; 
 unsigned long CGEN_INSN_BASE_VALUE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * CGEN_INSN_SYNTAX (int /*<<< orphan*/  const*) ; 
 scalar_t__ CGEN_SYNTAX_CHAR_P (scalar_t__ const) ; 
 int /*<<< orphan*/  CGEN_SYNTAX_FIELD (scalar_t__ const) ; 
 scalar_t__* CGEN_SYNTAX_STRING (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cgen_put_insn_value (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  put_insn_int_value (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,unsigned long) ; 
 char* stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
insert_insn_normal (CGEN_CPU_DESC cd,
		    const CGEN_INSN * insn,
		    CGEN_FIELDS * fields,
		    CGEN_INSN_BYTES_PTR buffer,
		    bfd_vma pc)
{
  const CGEN_SYNTAX *syntax = CGEN_INSN_SYNTAX (insn);
  unsigned long value;
  const CGEN_SYNTAX_CHAR_TYPE * syn;

  CGEN_INIT_INSERT (cd);
  value = CGEN_INSN_BASE_VALUE (insn);

  /* If we're recording insns as numbers (rather than a string of bytes),
     target byte order handling is deferred until later.  */

#if CGEN_INT_INSN_P

  put_insn_int_value (cd, buffer, cd->base_insn_bitsize,
		      CGEN_FIELDS_BITSIZE (fields), value);

#else

  cgen_put_insn_value (cd, buffer, min ((unsigned) cd->base_insn_bitsize,
					(unsigned) CGEN_FIELDS_BITSIZE (fields)),
		       value);

#endif /* ! CGEN_INT_INSN_P */

  /* ??? It would be better to scan the format's fields.
     Still need to be able to insert a value based on the operand though;
     e.g. storing a branch displacement that got resolved later.
     Needs more thought first.  */

  for (syn = CGEN_SYNTAX_STRING (syntax); * syn; ++ syn)
    {
      const char *errmsg;

      if (CGEN_SYNTAX_CHAR_P (* syn))
	continue;

      errmsg = (* cd->insert_operand) (cd, CGEN_SYNTAX_FIELD (*syn),
				       fields, buffer, pc);
      if (errmsg)
	return errmsg;
    }

  return NULL;
}