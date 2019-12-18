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
typedef  enum cgen_parse_operand_type { ____Placeholder_cgen_parse_operand_type } cgen_parse_operand_type ;
typedef  enum cgen_parse_operand_result { ____Placeholder_cgen_parse_operand_result } cgen_parse_operand_result ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  CGEN_CPU_DESC ;

/* Variables and functions */
 int CGEN_PARSE_OPERAND_ADDRESS ; 
 int CGEN_PARSE_OPERAND_INTEGER ; 
 char const* gas_cgen_parse_operand (int /*<<< orphan*/ ,int,char const**,int,int,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
mep_parse_operand (CGEN_CPU_DESC cd, enum cgen_parse_operand_type want,
		   const char **strP, int opindex, int opinfo,
		   enum cgen_parse_operand_result *resultP, bfd_vma *valueP)
{
  if (want == CGEN_PARSE_OPERAND_INTEGER || want == CGEN_PARSE_OPERAND_ADDRESS)
    {
      const char *next;

      next = *strP;
      while (*next == '(')
	next++;
      if (*next == '$')
	return "Not a valid literal";
    }
  return gas_cgen_parse_operand (cd, want, strP, opindex, opinfo,
				 resultP, valueP);
}