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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  TOUPPER (char const) ; 
 char* XSTR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putchar (int /*<<< orphan*/ ) ; 
 char* scan_comma_elt (char const**) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  write_extract_subexp (char const*) ; 

__attribute__((used)) static void
write_match_code_switch (rtx exp)
{
  const char *codes = XSTR (exp, 0);
  const char *path = XSTR (exp, 1);
  const char *code;

  fputs ("  switch (GET_CODE (", stdout);
  write_extract_subexp (path);
  fputs ("))\n    {\n", stdout);

  while ((code = scan_comma_elt (&codes)) != 0)
    {
      fputs ("    case ", stdout);
      while (code < codes)
	{
	  putchar (TOUPPER (*code));
	  code++;
	}
      fputs(":\n", stdout);
    }
}