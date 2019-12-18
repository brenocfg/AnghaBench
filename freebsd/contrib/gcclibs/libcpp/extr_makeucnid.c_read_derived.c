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
 int /*<<< orphan*/  fail (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 int* flags ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int maybe_not_NFC ; 
 int not_NFC ; 
 int not_NFKC ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 unsigned long strtoul (char*,char**,int) ; 

__attribute__((used)) static void
read_derived (const char *fname)
{
  FILE * f = fopen (fname, "r");
  
  if (!f)
    fail ("opening DerivedNormalizationProps.txt");
  for (;;)
    {
      char line[256];
      unsigned long start, end;
      char *l;
      bool not_NFC_p, not_NFKC_p, maybe_not_NFC_p;

      if (!fgets (line, sizeof (line), f))
	break;
      not_NFC_p = (strstr (line, "; NFC_QC; N") != NULL);
      not_NFKC_p = (strstr (line, "; NFKC_QC; N") != NULL);
      maybe_not_NFC_p = (strstr (line, "; NFC_QC; M") != NULL);
      if (! not_NFC_p && ! not_NFKC_p && ! maybe_not_NFC_p)
	continue;
	
      start = strtoul (line, &l, 16);
      if (l == line)
	fail ("parsing DerivedNormalizationProps.txt, reading start");
      if (start > 0xffff)
	continue;
      if (*l == '.' && l[1] == '.')
	end = strtoul (l + 2, &l, 16);
      else
	end = start;

      while (start <= end)
	flags[start++] |= ((not_NFC_p ? not_NFC : 0) 
			   | (not_NFKC_p ? not_NFKC : 0)
			   | (maybe_not_NFC_p ? maybe_not_NFC : 0)
			   );
    }
  if (ferror (f))
    fail ("reading DerivedNormalizationProps.txt");
  fclose (f);
}