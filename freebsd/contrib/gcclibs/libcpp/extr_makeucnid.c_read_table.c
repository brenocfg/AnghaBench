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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int C99 ; 
 int CXX ; 
 void** combining_value ; 
 unsigned long** decomp ; 
 int digit ; 
 int /*<<< orphan*/  fail (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 int* flags ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  isxdigit (char) ; 
 void* strtoul (char*,char**,int) ; 

__attribute__((used)) static void
read_table (char *fname)
{
  FILE * f = fopen (fname, "r");
  
  if (!f)
    fail ("opening UnicodeData.txt");
  for (;;)
    {
      char line[256];
      unsigned long codepoint, this_decomp[4];
      char *l;
      int i;
      int decomp_useful;

      if (!fgets (line, sizeof (line), f))
	break;
      codepoint = strtoul (line, &l, 16);
      if (l == line || *l != ';')
	fail ("parsing UnicodeData.txt, reading code point");
      if (codepoint > 0xffff || ! (flags[codepoint] & (C99 | CXX)))
	continue;

      do {
	l++;
      } while (*l != ';');
      /* Category value; things starting with 'N' are numbers of some
	 kind.  */
      if (*++l == 'N')
	flags[codepoint] |= digit;

      do {
	l++;
      } while (*l != ';');
      /* Canonical combining class; in NFC/NFKC, they must be increasing
	 (or zero).  */
      if (! isdigit (*++l))
	fail ("parsing UnicodeData.txt, combining class not number");
      combining_value[codepoint] = strtoul (l, &l, 10);
      if (*l++ != ';')
	fail ("parsing UnicodeData.txt, junk after combining class");
	
      /* Skip over bidi value.  */
      do {
	l++;
      } while (*l != ';');
      
      /* Decomposition mapping.  */
      decomp_useful = flags[codepoint];
      if (*++l == '<')  /* Compatibility mapping. */
	continue;
      for (i = 0; i < 4; i++)
	{
	  if (*l == ';')
	    break;
	  if (!isxdigit (*l))
	    fail ("parsing UnicodeData.txt, decomposition format");
	  this_decomp[i] = strtoul (l, &l, 16);
	  decomp_useful &= flags[this_decomp[i]];
	  while (isspace (*l))
	    l++;
	}
      if (i > 2)  /* Decomposition too long.  */
	fail ("parsing UnicodeData.txt, decomposition too long");
      if (decomp_useful)
	while (--i >= 0)
	  decomp[codepoint][i] = this_decomp[i];
    }
  if (ferror (f))
    fail ("reading UnicodeData.txt");
  fclose (f);
}