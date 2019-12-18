#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum cgen_parse_operand_result { ____Placeholder_cgen_parse_operand_result } cgen_parse_operand_result ;
typedef  long bfd_vma ;
struct TYPE_4__ {char* (* parse_operand_fn ) (TYPE_1__*,int /*<<< orphan*/ ,char const**,int,int /*<<< orphan*/ ,int*,long*) ;} ;
typedef  TYPE_1__* CGEN_CPU_DESC ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_RELOC_NONE ; 
 int /*<<< orphan*/  CGEN_PARSE_OPERAND_INTEGER ; 
 char* stub1 (TYPE_1__*,int /*<<< orphan*/ ,char const**,int,int /*<<< orphan*/ ,int*,long*) ; 

const char *
cgen_parse_signed_integer (CGEN_CPU_DESC cd,
			   const char **strp,
			   int opindex,
			   long *valuep)
{
  bfd_vma value;
  enum cgen_parse_operand_result result;
  const char *errmsg;

  errmsg = (* cd->parse_operand_fn)
    (cd, CGEN_PARSE_OPERAND_INTEGER, strp, opindex, BFD_RELOC_NONE,
     &result, &value);
  /* FIXME: Examine `result'.  */
  if (!errmsg)
    *valuep = value;
  return errmsg;
}