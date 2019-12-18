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
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  CGEN_CPU_DESC ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_RELOC_MEP_GPREL ; 
 int /*<<< orphan*/  BFD_RELOC_MEP_HI16S ; 
 int /*<<< orphan*/  BFD_RELOC_MEP_HI16U ; 
 int /*<<< orphan*/  BFD_RELOC_MEP_LOW16 ; 
 int /*<<< orphan*/  BFD_RELOC_MEP_TPREL ; 
 int CGEN_PARSE_OPERAND_RESULT_NUMBER ; 
 char const* _ (char*) ; 
 char* cgen_parse_address (int /*<<< orphan*/ ,char const**,int,int /*<<< orphan*/ ,int*,int*) ; 
 char const* cgen_parse_signed_integer (int /*<<< orphan*/ ,char const**,int,long*) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 

__attribute__((used)) static const char *
parse_lo16 (CGEN_CPU_DESC cd,
	    const char **strp,
	    int opindex,
	    long *valuep,
	    long signedp)
{
  const char *errmsg;
  enum cgen_parse_operand_result result_type;
  bfd_vma value;

  if (strncasecmp (*strp, "%lo(", 4) == 0)
    {
      *strp += 4;
      errmsg = cgen_parse_address (cd, strp, opindex, BFD_RELOC_MEP_LOW16,
				   & result_type, & value);
      if (**strp != ')')
	return _("missing `)'");
      ++*strp;
      if (errmsg == NULL
	  && result_type == CGEN_PARSE_OPERAND_RESULT_NUMBER)
	value &= 0xffff;
      if (signedp)
	*valuep = (long)(short) value;
      else
	*valuep = value;
      return errmsg;
    }

  if (strncasecmp (*strp, "%hi(", 4) == 0)
    {
      *strp += 4;
      errmsg = cgen_parse_address (cd, strp, opindex, BFD_RELOC_MEP_HI16S,
				   & result_type, & value);
      if (**strp != ')')
	return _("missing `)'");
      ++*strp;
      if (errmsg == NULL
	  && result_type == CGEN_PARSE_OPERAND_RESULT_NUMBER)
	value = (value + 0x8000) >> 16;
      *valuep = value;
      return errmsg;
    }

  if (strncasecmp (*strp, "%uhi(", 5) == 0)
    {
      *strp += 5;
      errmsg = cgen_parse_address (cd, strp, opindex, BFD_RELOC_MEP_HI16U,
				   & result_type, & value);
      if (**strp != ')')
	return _("missing `)'");
      ++*strp;
      if (errmsg == NULL
	  && result_type == CGEN_PARSE_OPERAND_RESULT_NUMBER)
	value = value >> 16;
      *valuep = value;
      return errmsg;
    }

  if (strncasecmp (*strp, "%sdaoff(", 8) == 0)
    {
      *strp += 8;
      errmsg = cgen_parse_address (cd, strp, opindex, BFD_RELOC_MEP_GPREL,
				   NULL, & value);
      if (**strp != ')')
	return _("missing `)'");
      ++*strp;
      *valuep = value;
      return errmsg;
    }

  if (strncasecmp (*strp, "%tpoff(", 7) == 0)
    {
      *strp += 7;
      errmsg = cgen_parse_address (cd, strp, opindex, BFD_RELOC_MEP_TPREL,
				   NULL, & value);
      if (**strp != ')')
	return _("missing `)'");
      ++*strp;
      *valuep = value;
      return errmsg;
    }

  if (**strp == '%')
    return _("invalid %function() here");

  return cgen_parse_signed_integer (cd, strp, opindex, valuep);
}