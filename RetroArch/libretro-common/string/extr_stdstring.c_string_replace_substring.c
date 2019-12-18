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
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 char* strdup (char const*) ; 
 size_t strlen (char const*) ; 
 char* strstr (char const*,char const*) ; 

char *string_replace_substring(const char *in,
      const char *pattern, const char *replacement)
{
   size_t numhits, pattern_len, replacement_len, outlen;
   const char *inat   = NULL;
   const char *inprev = NULL;
   char          *out = NULL;
   char        *outat = NULL;

   /* if either pattern or replacement is NULL,
    * duplicate in and let caller handle it. */
   if (!pattern || !replacement)
      return strdup(in);

   pattern_len     = strlen(pattern);
   replacement_len = strlen(replacement);
   numhits         = 0;
   inat            = in;

   while ((inat = strstr(inat, pattern)))
   {
      inat += pattern_len;
      numhits++;
   }

   outlen          = strlen(in) - pattern_len*numhits + replacement_len*numhits;
   out             = (char *)malloc(outlen+1);

   if (!out)
      return NULL;

   outat           = out;
   inat            = in;
   inprev          = in;

   while ((inat = strstr(inat, pattern)))
   {
      memcpy(outat, inprev, inat-inprev);
      outat += inat-inprev;
      memcpy(outat, replacement, replacement_len);
      outat += replacement_len;
      inat += pattern_len;
      inprev = inat;
   }
   strcpy(outat, inprev);

   return out;
}