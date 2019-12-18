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
typedef  int /*<<< orphan*/  CGEN_KEYWORD ;
typedef  int /*<<< orphan*/  CGEN_CPU_DESC ;

/* Variables and functions */
 char const* _ (char*) ; 
 char* cgen_parse_keyword (int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ *,long*) ; 

const char *
parse_spreg (CGEN_CPU_DESC cd, const char ** strp,
	     CGEN_KEYWORD *keyword_table, long *field)
{
  const char *err;

  err = cgen_parse_keyword (cd, strp, keyword_table, field);
  if (err)
    return err;
  if (*field != 15)
    return _("Only $sp or $15 allowed for this opcode");
  return NULL;
}