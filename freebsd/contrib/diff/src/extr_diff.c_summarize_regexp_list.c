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
struct regexp_list {char* regexps; TYPE_1__* buf; int /*<<< orphan*/  len; scalar_t__ multiple_regexps; } ;
struct TYPE_2__ {int /*<<< orphan*/  fastmap; } ;

/* Variables and functions */
 int CHAR_BIT ; 
 int /*<<< orphan*/  EXIT_TROUBLE ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char const*) ; 
 char* re_compile_pattern (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  xmalloc (int) ; 

__attribute__((used)) static void
summarize_regexp_list (struct regexp_list *reglist)
{
  if (reglist->regexps)
    {
      /* At least one regexp was specified.  Allocate a fastmap for it.  */
      reglist->buf->fastmap = xmalloc (1 << CHAR_BIT);
      if (reglist->multiple_regexps)
	{
	  /* Compile the disjunction of the regexps.
	     (If just one regexp was specified, it is already compiled.)  */
	  char const *m = re_compile_pattern (reglist->regexps, reglist->len,
					      reglist->buf);
	  if (m != 0)
	    error (EXIT_TROUBLE, 0, "%s: %s", reglist->regexps, m);
	}
    }
}