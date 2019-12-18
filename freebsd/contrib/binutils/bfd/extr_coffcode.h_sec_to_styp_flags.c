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
typedef  int flagword ;

/* Variables and functions */
 scalar_t__ CONST_STRNEQ (char const*,char*) ; 
 char* DOT_DEBUG ; 
 char* GNU_LINKONCE_WI ; 
 int SEC_ALLOC ; 
 int SEC_CODE ; 
 int SEC_COFF_SHARED_LIBRARY ; 
 int SEC_DATA ; 
 int SEC_LOAD ; 
 int SEC_NEVER_LOAD ; 
 int SEC_READONLY ; 
 int SEC_TIC54X_BLOCK ; 
 int SEC_TIC54X_CLINK ; 
 long STYP_BLOCK ; 
 long STYP_BSS ; 
 long STYP_CLINK ; 
 long STYP_DATA ; 
 long STYP_DEBUG_INFO ; 
 long STYP_EXCEPT ; 
 long STYP_INFO ; 
 long STYP_LIB ; 
 long STYP_LIT ; 
 long STYP_LOADER ; 
 long STYP_NOLOAD ; 
 long STYP_PAD ; 
 long STYP_TEXT ; 
 long STYP_TYPCHK ; 
 long STYP_XCOFF_DEBUG ; 
 int /*<<< orphan*/  _BSS ; 
 int /*<<< orphan*/  _COMMENT ; 
 int /*<<< orphan*/  _DATA ; 
 int /*<<< orphan*/  _EXCEPT ; 
 int /*<<< orphan*/  _LIB ; 
 int /*<<< orphan*/  _LIT ; 
 int /*<<< orphan*/  _LOADER ; 
 int /*<<< orphan*/  _PAD ; 
 int /*<<< orphan*/  _TEXT ; 
 int /*<<< orphan*/  _TYPCHK ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long
sec_to_styp_flags (const char *sec_name, flagword sec_flags)
{
  long styp_flags = 0;

  if (!strcmp (sec_name, _TEXT))
    {
      styp_flags = STYP_TEXT;
    }
  else if (!strcmp (sec_name, _DATA))
    {
      styp_flags = STYP_DATA;
    }
  else if (!strcmp (sec_name, _BSS))
    {
      styp_flags = STYP_BSS;
#ifdef _COMMENT
    }
  else if (!strcmp (sec_name, _COMMENT))
    {
      styp_flags = STYP_INFO;
#endif /* _COMMENT */
#ifdef _LIB
    }
  else if (!strcmp (sec_name, _LIB))
    {
      styp_flags = STYP_LIB;
#endif /* _LIB */
#ifdef _LIT
    }
  else if (!strcmp (sec_name, _LIT))
    {
      styp_flags = STYP_LIT;
#endif /* _LIT */
    }
  else if (CONST_STRNEQ (sec_name, DOT_DEBUG))
    {
      /* Handle the XCOFF debug section and DWARF2 debug sections.  */
      if (!sec_name[6])
        styp_flags = STYP_XCOFF_DEBUG;
      else
        styp_flags = STYP_DEBUG_INFO;
    }
  else if (CONST_STRNEQ (sec_name, ".stab"))
    {
      styp_flags = STYP_DEBUG_INFO;
    }
#ifdef COFF_LONG_SECTION_NAMES
  else if (CONST_STRNEQ (sec_name, GNU_LINKONCE_WI))
    {
      styp_flags = STYP_DEBUG_INFO;
    }
#endif
#ifdef RS6000COFF_C
  else if (!strcmp (sec_name, _PAD))
    {
      styp_flags = STYP_PAD;
    }
  else if (!strcmp (sec_name, _LOADER))
    {
      styp_flags = STYP_LOADER;
    }
  else if (!strcmp (sec_name, _EXCEPT))
    {
      styp_flags = STYP_EXCEPT;
    }
  else if (!strcmp (sec_name, _TYPCHK))
    {
      styp_flags = STYP_TYPCHK;
    }
#endif
  /* Try and figure out what it should be */
  else if (sec_flags & SEC_CODE)
    {
      styp_flags = STYP_TEXT;
    }
  else if (sec_flags & SEC_DATA)
    {
      styp_flags = STYP_DATA;
    }
  else if (sec_flags & SEC_READONLY)
    {
#ifdef STYP_LIT			/* 29k readonly text/data section */
      styp_flags = STYP_LIT;
#else
      styp_flags = STYP_TEXT;
#endif /* STYP_LIT */
    }
  else if (sec_flags & SEC_LOAD)
    {
      styp_flags = STYP_TEXT;
    }
  else if (sec_flags & SEC_ALLOC)
    {
      styp_flags = STYP_BSS;
    }

#ifdef STYP_CLINK
  if (sec_flags & SEC_TIC54X_CLINK)
    styp_flags |= STYP_CLINK;
#endif

#ifdef STYP_BLOCK
  if (sec_flags & SEC_TIC54X_BLOCK)
    styp_flags |= STYP_BLOCK;
#endif

#ifdef STYP_NOLOAD
  if ((sec_flags & (SEC_NEVER_LOAD | SEC_COFF_SHARED_LIBRARY)) != 0)
    styp_flags |= STYP_NOLOAD;
#endif

  return styp_flags;
}