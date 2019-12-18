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
typedef  scalar_t__ unichar ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* convert_unicode_to_ACP (scalar_t__ const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  unichar_len (scalar_t__ const*) ; 
 int /*<<< orphan*/  unicode_print (int /*<<< orphan*/ *,scalar_t__ const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
write_dbg_define (FILE *fp, const unichar *sym_name, const unichar *typecast)
{
  char *sym;

  if (!sym_name || sym_name[0] == 0)
    return;
  sym = convert_unicode_to_ACP (sym_name);
  fprintf (fp, "  {(");
  if (typecast)
    unicode_print (fp, typecast, unichar_len (typecast));
  else
    fprintf (fp, "DWORD");
  fprintf (fp, ") %s, \"%s\" },\n", sym, sym);
}