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
typedef  scalar_t__ png_uint_16 ;
typedef  int /*<<< orphan*/  png_structp ;
typedef  int /*<<< orphan*/  png_infop ;
typedef  char** png_charpp ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  png_set_hIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stderr ; 
 unsigned long strtoul (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
insert_hIST(png_structp png_ptr, png_infop info_ptr, int nparams,
      png_charpp params)
{
   int i;
   png_uint_16 freq[256];

   /* libpng takes the count from the PLTE count; we don't check it here but we
    * do set the array to 0 for unspecified entries.
    */
   memset(freq, 0, sizeof freq);
   for (i=0; i<nparams; ++i)
   {
      char *endptr = NULL;
      unsigned long int l = strtoul(params[i], &endptr, 0/*base*/);

      if (params[i][0] && *endptr == 0 && l <= 65535)
         freq[i] = (png_uint_16)l;

      else
      {
         fprintf(stderr, "hIST[%d]: %s: invalid frequency\n", i, params[i]);
         exit(1);
      }
   }

   png_set_hIST(png_ptr, info_ptr, freq);
}