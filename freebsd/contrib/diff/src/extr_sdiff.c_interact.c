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
typedef  scalar_t__ uintmax_t ;
struct line_filter {int dummy; } ;
typedef  scalar_t__ lin ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ MAX (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  checksigs () ; 
 int /*<<< orphan*/  edit (struct line_filter*,char const*,scalar_t__,scalar_t__,struct line_filter*,char const*,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  lf_copy (struct line_filter*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lf_skip (struct line_filter*,scalar_t__) ; 
 int lf_snarf (struct line_filter*,char*,int) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ strtoumax (char*,char**,int) ; 
 int /*<<< orphan*/  suppress_common_lines ; 

__attribute__((used)) static bool
interact (struct line_filter *diff,
	  struct line_filter *left, char const *lname,
	  struct line_filter *right, char const *rname,
	  FILE *outfile)
{
  lin lline = 1, rline = 1;

  for (;;)
    {
      char diff_help[256];
      int snarfed = lf_snarf (diff, diff_help, sizeof diff_help);

      if (snarfed <= 0)
	return snarfed != 0;

      checksigs ();

      if (diff_help[0] == ' ')
	puts (diff_help + 1);
      else
	{
	  char *numend;
	  uintmax_t val;
	  lin llen, rlen, lenmax;
	  errno = 0;
	  llen = val = strtoumax (diff_help + 1, &numend, 10);
	  if (llen < 0 || llen != val || errno || *numend != ',')
	    fatal (diff_help);
	  rlen = val = strtoumax (numend + 1, &numend, 10);
	  if (rlen < 0 || rlen != val || errno || *numend)
	    fatal (diff_help);

	  lenmax = MAX (llen, rlen);

	  switch (diff_help[0])
	    {
	    case 'i':
	      if (suppress_common_lines)
		lf_skip (diff, lenmax);
	      else
		lf_copy (diff, lenmax, stdout);

	      lf_copy (left, llen, outfile);
	      lf_skip (right, rlen);
	      break;

	    case 'c':
	      lf_copy (diff, lenmax, stdout);
	      if (! edit (left, lname, lline, llen,
			  right, rname, rline, rlen,
			  outfile))
		return false;
	      break;

	    default:
	      fatal (diff_help);
	    }

	  lline += llen;
	  rline += rlen;
	}
    }
}