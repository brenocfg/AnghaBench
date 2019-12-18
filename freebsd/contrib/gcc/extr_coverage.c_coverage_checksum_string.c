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
 int /*<<< orphan*/  GLOBAL_PREFIX ; 
 int /*<<< orphan*/  ISCAPXDIGIT (char) ; 
 int NDIGITS ; 
 int /*<<< orphan*/  TRAILING_N ; 
 unsigned int crc32_string (unsigned int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strstr (char const*,int /*<<< orphan*/ ) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static unsigned
coverage_checksum_string (unsigned chksum, const char *string)
{
  char *dup = NULL;
  char *ptr;

  /* Look for everything that looks if it were produced by
     get_file_function_name and zero out the second part
     that may result from flag_random_seed.  This is not critical
     as the checksums are used only for sanity checking.  */
#define GLOBAL_PREFIX "_GLOBAL__"
#define TRAILING_N "N_"
#define ISCAPXDIGIT(a) (((a) >= '0' && (a) <= '9') || ((a) >= 'A' && (a) <= 'F'))
  if ((ptr = strstr (string, GLOBAL_PREFIX)))
    {
      /* Skip _GLOBAL__. */
      ptr += strlen (GLOBAL_PREFIX);

      /* Skip optional N_ (in case __GLOBAL_N__). */
      if (!strncmp (ptr, TRAILING_N, strlen (TRAILING_N)))
          ptr += strlen (TRAILING_N);
      /* At this point, ptr should point after "_GLOBAL__N_" or "_GLOBAL__". */

      while ((ptr = strchr (ptr, '_')) != NULL)
        {
          int y;
          /* For every "_" in the rest of the string,
             try the follwing pattern matching */

          /* Skip over '_'. */
          ptr++;
#define NDIGITS (8)
          /* Try matching the pattern:
             <8-digit hex>_<8-digit hex>
             The second number is randomly generated
             so we want to mask it out before computing the checksum. */
          for (y = 0; *ptr != 0 && y < NDIGITS; y++, ptr++)
              if (!ISCAPXDIGIT (*ptr))
                  break;
          if (y != NDIGITS || *ptr != '_')
              continue;
          /* Skip over '_' again. */
          ptr++;
          for (y = 0; *ptr != 0 && y < NDIGITS; y++, ptr++)
              if (!ISCAPXDIGIT (*ptr))
                  break;

          if (y == NDIGITS)
            {
              /* We have a match.
                 Duplicate the string and mask out
                 the second 8-digit number. */
              dup = xstrdup (string);
              ptr = dup + (ptr - string);
              for(y = -NDIGITS - 1 ; y < 0; y++)
                {
                  ptr[y] = '0';
                }
              ptr = dup;
              break;
            }
        }
        /* "ptr" should be NULL if we couldn't find the match
           (strchr will return NULL if no match is found),
           or it should point to dup which contains the string
           with the random part masked. */
    }

  chksum = crc32_string (chksum, (ptr) ? ptr : string);

  if (dup)
      free (dup);

  return chksum;
}