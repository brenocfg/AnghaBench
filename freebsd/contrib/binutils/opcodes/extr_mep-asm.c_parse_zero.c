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
typedef  enum cgen_parse_operand_result { ____Placeholder_cgen_parse_operand_result } cgen_parse_operand_result ;
typedef  long bfd_vma ;
typedef  int /*<<< orphan*/  CGEN_CPU_DESC ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_RELOC_MEP_GPREL ; 
 int /*<<< orphan*/  BFD_RELOC_MEP_HI16S ; 
 int /*<<< orphan*/  BFD_RELOC_MEP_HI16U ; 
 int /*<<< orphan*/  BFD_RELOC_MEP_LOW16 ; 
 int /*<<< orphan*/  BFD_RELOC_MEP_TPREL ; 
 int /*<<< orphan*/  BFD_RELOC_NONE ; 
 int CGEN_PARSE_OPERAND_RESULT_NUMBER ; 
 char* cgen_parse_address (int /*<<< orphan*/ ,char const**,int,int /*<<< orphan*/ ,int*,long*) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static const char *
parse_zero (CGEN_CPU_DESC cd, const char **strp, int opindex, long *valuep)
{
  const char *errmsg;
  enum cgen_parse_operand_result result_type;
  bfd_vma value;

  /*fprintf(stderr, "dj: signed parse opindex `%s'\n", *strp);*/

  /* Prevent ($ry) from being attempted as an expression on 'sw $rx,($ry)'.
     It will fail and cause ry to be listed as an undefined symbol in the
     listing.  */
  if (strncmp (*strp, "($", 2) == 0)
    return "not zero"; /* any string will do -- will never be seen.  */

  if (strncasecmp (*strp, "%lo(", 4) == 0)
    {
      *strp += 4;
      errmsg = cgen_parse_address (cd, strp, opindex, BFD_RELOC_MEP_LOW16,
				   &result_type, &value);
      if (**strp != ')')
	return "missing `)'";
      ++*strp;
      if (errmsg == NULL
	  && (result_type != CGEN_PARSE_OPERAND_RESULT_NUMBER || value != 0))
	return "not zero"; /* any string will do -- will never be seen.  */
      *valuep = value;
      return errmsg;
    }

  if (strncasecmp (*strp, "%hi(", 4) == 0)
    {
      *strp += 4;
      errmsg = cgen_parse_address (cd, strp, opindex, BFD_RELOC_MEP_HI16S,
				   &result_type, &value);
      if (**strp != ')')
	return "missing `)'";
      ++*strp;
      if (errmsg == NULL
	  && (result_type != CGEN_PARSE_OPERAND_RESULT_NUMBER || value != 0))
	return "not zero"; /* any string will do -- will never be seen.  */
      *valuep = value;
      return errmsg;
    }

  if (strncasecmp (*strp, "%uhi(", 5) == 0)
    {
      *strp += 5;
      errmsg = cgen_parse_address (cd, strp, opindex, BFD_RELOC_MEP_HI16U,
				   &result_type, &value);
      if (**strp != ')')
	return "missing `)'";
      ++*strp;
      if (errmsg == NULL
	  && (result_type != CGEN_PARSE_OPERAND_RESULT_NUMBER || value != 0))
	return "not zero"; /* any string will do -- will never be seen.  */
      *valuep = value;
      return errmsg;
    }

  if (strncasecmp (*strp, "%sdaoff(", 8) == 0)
    {
      *strp += 8;
      errmsg = cgen_parse_address (cd, strp, opindex, BFD_RELOC_MEP_GPREL,
				   &result_type, &value);
      if (**strp != ')')
	return "missing `)'";
      ++*strp;
      if (errmsg == NULL
	  && (result_type != CGEN_PARSE_OPERAND_RESULT_NUMBER || value != 0))
	return "not zero"; /* any string will do -- will never be seen.  */
      *valuep = value;
      return errmsg;
    }

  if (strncasecmp (*strp, "%tpoff(", 7) == 0)
    {
      *strp += 7;
      errmsg = cgen_parse_address (cd, strp, opindex, BFD_RELOC_MEP_TPREL,
				   &result_type, &value);
      if (**strp != ')')
	return "missing `)'";
      ++*strp;
      if (errmsg == NULL
	  && (result_type != CGEN_PARSE_OPERAND_RESULT_NUMBER || value != 0))
	return "not zero"; /* any string will do -- will never be seen.  */
      *valuep = value;
      return errmsg;
    }

  if (**strp == '%')
    return "invalid %function() here";

  errmsg = cgen_parse_address (cd, strp, opindex, BFD_RELOC_NONE,
			       &result_type, &value);
  if (errmsg == NULL
      && (result_type != CGEN_PARSE_OPERAND_RESULT_NUMBER || value != 0))
    return "not zero"; /* any string will do -- will never be seen.  */

  return errmsg;
}