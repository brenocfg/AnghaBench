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

/* Variables and functions */
 int /*<<< orphan*/  TOUPPER (char const) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putchar (int /*<<< orphan*/ ) ; 
 char* scan_comma_elt (char const**) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  write_extract_subexp (char const*) ; 

__attribute__((used)) static void
write_match_code (const char *path, const char *codes)
{
  const char *code;

  while ((code = scan_comma_elt (&codes)) != 0)
    {
      fputs ("GET_CODE (", stdout);
      write_extract_subexp (path);
      fputs (") == ", stdout);
      while (code < codes)
	{
	  putchar (TOUPPER (*code));
	  code++;
	}
      
      if (*codes == ',')
	fputs (" || ", stdout);
    }
}