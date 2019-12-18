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
typedef  int bfd_vma ;
typedef  scalar_t__ bfd_signed_vma ;
typedef  scalar_t__ bfd_boolean ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ ISDIGIT (int) ; 
 scalar_t__ ISLOWER (int) ; 
 scalar_t__ ISUPPER (int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ errno ; 
 unsigned long strtoul (char const*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn_stab (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_vma
parse_number (const char **pp, bfd_boolean *poverflow)
{
  unsigned long ul;
  const char *orig;

  if (poverflow != NULL)
    *poverflow = FALSE;

  orig = *pp;

  errno = 0;
  ul = strtoul (*pp, (char **) pp, 0);
  if (ul + 1 != 0 || errno == 0)
    {
      /* If bfd_vma is larger than unsigned long, and the number is
         meant to be negative, we have to make sure that we sign
         extend properly.  */
      if (*orig == '-')
	return (bfd_vma) (bfd_signed_vma) (long) ul;
      return (bfd_vma) ul;
    }

  /* Note that even though strtoul overflowed, it should have set *pp
     to the end of the number, which is where we want it.  */
  if (sizeof (bfd_vma) > sizeof (unsigned long))
    {
      const char *p;
      bfd_boolean neg;
      int base;
      bfd_vma over, lastdig;
      bfd_boolean overflow;
      bfd_vma v;

      /* Our own version of strtoul, for a bfd_vma.  */
      p = orig;

      neg = FALSE;
      if (*p == '+')
	++p;
      else if (*p == '-')
	{
	  neg = TRUE;
	  ++p;
	}

      base = 10;
      if (*p == '0')
	{
	  if (p[1] == 'x' || p[1] == 'X')
	    {
	      base = 16;
	      p += 2;
	    }
	  else
	    {
	      base = 8;
	      ++p;
	    }
	}

      over = ((bfd_vma) (bfd_signed_vma) -1) / (bfd_vma) base;
      lastdig = ((bfd_vma) (bfd_signed_vma) -1) % (bfd_vma) base;

      overflow = FALSE;
      v = 0;
      while (1)
	{
	  int d;

	  d = *p++;
	  if (ISDIGIT (d))
	    d -= '0';
	  else if (ISUPPER (d))
	    d -= 'A';
	  else if (ISLOWER (d))
	    d -= 'a';
	  else
	    break;

	  if (d >= base)
	    break;

	  if (v > over || (v == over && (bfd_vma) d > lastdig))
	    {
	      overflow = TRUE;
	      break;
	    }
	}

      if (! overflow)
	{
	  if (neg)
	    v = - v;
	  return v;
	}
    }

  /* If we get here, the number is too large to represent in a
     bfd_vma.  */
  if (poverflow != NULL)
    *poverflow = TRUE;
  else
    warn_stab (orig, _("numeric overflow"));

  return 0;
}