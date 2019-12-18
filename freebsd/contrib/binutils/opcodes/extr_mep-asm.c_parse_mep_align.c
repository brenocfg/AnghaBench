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
typedef  enum cgen_operand_type { ____Placeholder_cgen_operand_type } cgen_operand_type ;
typedef  int /*<<< orphan*/  CGEN_CPU_DESC ;

/* Variables and functions */
#define  MEP_OPERAND_ADDR24A4 140 
#define  MEP_OPERAND_CDISP8A2 139 
#define  MEP_OPERAND_CDISP8A4 138 
#define  MEP_OPERAND_CDISP8A8 137 
#define  MEP_OPERAND_PCABS24A2 136 
#define  MEP_OPERAND_PCREL12A2 135 
#define  MEP_OPERAND_PCREL17A2 134 
#define  MEP_OPERAND_PCREL24A2 133 
#define  MEP_OPERAND_PCREL8A2 132 
#define  MEP_OPERAND_UDISP7 131 
#define  MEP_OPERAND_UDISP7A2 130 
#define  MEP_OPERAND_UDISP7A4 129 
#define  MEP_OPERAND_UIMM7A4 128 
 int /*<<< orphan*/  abort () ; 
 char* cgen_parse_signed_integer (int /*<<< orphan*/ ,char const**,int,long*) ; 
 char* cgen_parse_unsigned_integer (int /*<<< orphan*/ ,char const**,int,unsigned long*) ; 

const char *
parse_mep_align (CGEN_CPU_DESC cd, const char ** strp,
		 enum cgen_operand_type type, long *field)
{
  long lsbs = 0;
  const char *err;

  switch (type)
    {
    case MEP_OPERAND_PCREL8A2:
    case MEP_OPERAND_PCREL12A2:
    case MEP_OPERAND_PCREL17A2:
    case MEP_OPERAND_PCREL24A2:
    case MEP_OPERAND_CDISP8A2:
    case MEP_OPERAND_CDISP8A4:
    case MEP_OPERAND_CDISP8A8:
      err = cgen_parse_signed_integer   (cd, strp, type, field);
      break;
    case MEP_OPERAND_PCABS24A2:
    case MEP_OPERAND_UDISP7:
    case MEP_OPERAND_UDISP7A2:
    case MEP_OPERAND_UDISP7A4:
    case MEP_OPERAND_UIMM7A4:
    case MEP_OPERAND_ADDR24A4:
      err = cgen_parse_unsigned_integer (cd, strp, type, (unsigned long *) field);
      break;
    default:
      abort();
    }
  if (err)
    return err;
  switch (type)
    {
    case MEP_OPERAND_UDISP7:
      lsbs = 0;
      break;
    case MEP_OPERAND_PCREL8A2:
    case MEP_OPERAND_PCREL12A2:
    case MEP_OPERAND_PCREL17A2:
    case MEP_OPERAND_PCREL24A2:
    case MEP_OPERAND_PCABS24A2:
    case MEP_OPERAND_UDISP7A2:
    case MEP_OPERAND_CDISP8A2:
      lsbs = *field & 1;
      break;
    case MEP_OPERAND_UDISP7A4:
    case MEP_OPERAND_UIMM7A4:
    case MEP_OPERAND_ADDR24A4:
    case MEP_OPERAND_CDISP8A4:
      lsbs = *field & 3;
      break;
    case MEP_OPERAND_CDISP8A8:
      lsbs = *field & 7;
      break;
    default:
      /* Safe assumption?  */
      abort ();
    }
  if (lsbs)
    return "Value is not aligned enough";
  return NULL;
}