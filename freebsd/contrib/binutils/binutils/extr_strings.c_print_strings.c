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
typedef  int /*<<< orphan*/  start ;
typedef  int file_off ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 long EOF ; 
 int /*<<< orphan*/  STRING_ISGRAPHIC (long) ; 
 int address_radix ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 long get_char (int /*<<< orphan*/ *,int*,int*,char**) ; 
 scalar_t__ print_addresses ; 
 scalar_t__ print_filenames ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  stdout ; 
 int string_min ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
print_strings (const char *filename, FILE *stream, file_off address,
	       int stop_point, int magiccount, char *magic)
{
  char *buf = (char *) xmalloc (sizeof (char) * (string_min + 1));

  while (1)
    {
      file_off start;
      int i;
      long c;

      /* See if the next `string_min' chars are all graphic chars.  */
    tryline:
      if (stop_point && address >= stop_point)
	break;
      start = address;
      for (i = 0; i < string_min; i++)
	{
	  c = get_char (stream, &address, &magiccount, &magic);
	  if (c == EOF)
	    return;
	  if (! STRING_ISGRAPHIC (c))
	    /* Found a non-graphic.  Try again starting with next char.  */
	    goto tryline;
	  buf[i] = c;
	}

      /* We found a run of `string_min' graphic characters.  Print up
	 to the next non-graphic character.  */

      if (print_filenames)
	printf ("%s: ", filename);
      if (print_addresses)
	switch (address_radix)
	  {
	  case 8:
#if __STDC_VERSION__ >= 199901L || (defined(__GNUC__) && __GNUC__ >= 2)
	    if (sizeof (start) > sizeof (long))
	      printf ("%7llo ", (unsigned long long) start);
	    else
#else
# if !BFD_HOST_64BIT_LONG
	    if (start != (unsigned long) start)
	      printf ("++%7lo ", (unsigned long) start);
	    else
# endif
#endif
	      printf ("%7lo ", (unsigned long) start);
	    break;

	  case 10:
#if __STDC_VERSION__ >= 199901L || (defined(__GNUC__) && __GNUC__ >= 2)
	    if (sizeof (start) > sizeof (long))
	      printf ("%7lld ", (unsigned long long) start);
	    else
#else
# if !BFD_HOST_64BIT_LONG
	    if (start != (unsigned long) start)
	      printf ("++%7ld ", (unsigned long) start);
	    else
# endif
#endif
	      printf ("%7ld ", (long) start);
	    break;

	  case 16:
#if __STDC_VERSION__ >= 199901L || (defined(__GNUC__) && __GNUC__ >= 2)
	    if (sizeof (start) > sizeof (long))
	      printf ("%7llx ", (unsigned long long) start);
	    else
#else
# if !BFD_HOST_64BIT_LONG
	    if (start != (unsigned long) start)
	      printf ("%lx%8.8lx ", (unsigned long) (start >> 32),
		      (unsigned long) (start & 0xffffffff));
	    else
# endif
#endif
	      printf ("%7lx ", (unsigned long) start);
	    break;
	  }

      buf[i] = '\0';
      fputs (buf, stdout);

      while (1)
	{
	  c = get_char (stream, &address, &magiccount, &magic);
	  if (c == EOF)
	    break;
	  if (! STRING_ISGRAPHIC (c))
	    break;
	  putchar (c);
	}

      putchar ('\n');
    }
}