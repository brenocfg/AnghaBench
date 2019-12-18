#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct normalize_state {scalar_t__ prev_class; int previous; void* level; } ;
typedef  int cppchar_t ;
typedef  int /*<<< orphan*/  cpp_reader ;
struct TYPE_3__ {int end; int flags; scalar_t__ combine; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int C99 ; 
 int CID ; 
 int /*<<< orphan*/  CPP_DL_ICE ; 
 scalar_t__ CPP_OPTION (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ CPP_PEDANTIC (int /*<<< orphan*/ *) ; 
 int CTX ; 
 int CXX ; 
 int DIG ; 
 void* MAX (void*,int /*<<< orphan*/ ) ; 
 int NFC ; 
 int NKC ; 
 int /*<<< orphan*/  c99 ; 
 int /*<<< orphan*/  cplusplus ; 
 int /*<<< orphan*/  cpp_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  normalized_C ; 
 int /*<<< orphan*/  normalized_identifier_C ; 
 void* normalized_none ; 
 TYPE_1__* ucnranges ; 

__attribute__((used)) static int
ucn_valid_in_identifier (cpp_reader *pfile, cppchar_t c,
			 struct normalize_state *nst)
{
  int mn, mx, md;

  if (c > 0xFFFF)
    return 0;

  mn = 0;
  mx = ARRAY_SIZE (ucnranges) - 1;
  while (mx != mn)
    {
      md = (mn + mx) / 2;
      if (c <= ucnranges[md].end)
	mx = md;
      else
	mn = md + 1;
    }

  /* When -pedantic, we require the character to have been listed by
     the standard for the current language.  Otherwise, we accept the
     union of the acceptable sets for C++98 and C99.  */
  if (! (ucnranges[mn].flags & (C99 | CXX)))
      return 0;

  if (CPP_PEDANTIC (pfile)
      && ((CPP_OPTION (pfile, c99) && !(ucnranges[mn].flags & C99))
	  || (CPP_OPTION (pfile, cplusplus)
	      && !(ucnranges[mn].flags & CXX))))
    return 0;

  /* Update NST.  */
  if (ucnranges[mn].combine != 0 && ucnranges[mn].combine < nst->prev_class)
    nst->level = normalized_none;
  else if (ucnranges[mn].flags & CTX)
    {
      bool safe;
      cppchar_t p = nst->previous;

      /* Easy cases from Bengali, Oriya, Tamil, Jannada, and Malayalam.  */
      if (c == 0x09BE)
	safe = p != 0x09C7;  /* Use 09CB instead of 09C7 09BE.  */
      else if (c == 0x0B3E)
	safe = p != 0x0B47;  /* Use 0B4B instead of 0B47 0B3E.  */
      else if (c == 0x0BBE)
	safe = p != 0x0BC6 && p != 0x0BC7;  /* Use 0BCA/0BCB instead.  */
      else if (c == 0x0CC2)
	safe = p != 0x0CC6;  /* Use 0CCA instead of 0CC6 0CC2.  */
      else if (c == 0x0D3E)
	safe = p != 0x0D46 && p != 0x0D47;  /* Use 0D4A/0D4B instead.  */
      /* For Hangul, characters in the range AC00-D7A3 are NFC/NFKC,
	 and are combined algorithmically from a sequence of the form
	 1100-1112 1161-1175 11A8-11C2
	 (if the third is not present, it is treated as 11A7, which is not
	 really a valid character).
	 Unfortunately, C99 allows (only) the NFC form, but C++ allows
	 only the combining characters.  */
      else if (c >= 0x1161 && c <= 0x1175)
	safe = p < 0x1100 || p > 0x1112;
      else if (c >= 0x11A8 && c <= 0x11C2)
	safe = (p < 0xAC00 || p > 0xD7A3 || (p - 0xAC00) % 28 != 0);
      else
	{
	  /* Uh-oh, someone updated ucnid.h without updating this code.  */
	  cpp_error (pfile, CPP_DL_ICE, "Character %x might not be NFKC", c);
	  safe = true;
	}
      if (!safe && c < 0x1161)
	nst->level = normalized_none;
      else if (!safe)
	nst->level = MAX (nst->level, normalized_identifier_C);
    }
  else if (ucnranges[mn].flags & NKC)
    ;
  else if (ucnranges[mn].flags & NFC)
    nst->level = MAX (nst->level, normalized_C);
  else if (ucnranges[mn].flags & CID)
    nst->level = MAX (nst->level, normalized_identifier_C);
  else
    nst->level = normalized_none;
  nst->previous = c;
  nst->prev_class = ucnranges[mn].combine;

  /* In C99, UCN digits may not begin identifiers.  */
  if (CPP_OPTION (pfile, c99) && (ucnranges[mn].flags & DIG))
    return 2;

  return 1;
}