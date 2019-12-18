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
 int SEC_ALLOC ; 
 int SEC_CODE ; 
 int SEC_COFF_SHARED_LIBRARY ; 
 int SEC_CONSTRUCTOR ; 
 int SEC_DATA ; 
 int SEC_HAS_CONTENTS ; 
 int SEC_IS_COMMON ; 
 int SEC_LOAD ; 
 int SEC_NEVER_LOAD ; 
 int SEC_READONLY ; 
 int SEC_RELOC ; 
 int SEC_ROM ; 
 scalar_t__ match_substring (char*,char*) ; 

__attribute__((used)) static int 
match_bfd_flags (char *string, flagword flags)
{
  if (flags & SEC_ALLOC)
    if (match_substring (string, "ALLOC"))
      return 1;
  if (flags & SEC_LOAD)
    if (match_substring (string, "LOAD"))
      return 1;
  if (flags & SEC_RELOC)
    if (match_substring (string, "RELOC"))
      return 1;
  if (flags & SEC_READONLY)
    if (match_substring (string, "READONLY"))
      return 1;
  if (flags & SEC_CODE)
    if (match_substring (string, "CODE"))
      return 1;
  if (flags & SEC_DATA)
    if (match_substring (string, "DATA"))
      return 1;
  if (flags & SEC_ROM)
    if (match_substring (string, "ROM"))
      return 1;
  if (flags & SEC_CONSTRUCTOR)
    if (match_substring (string, "CONSTRUCTOR"))
      return 1;
  if (flags & SEC_HAS_CONTENTS)
    if (match_substring (string, "HAS_CONTENTS"))
      return 1;
  if (flags & SEC_NEVER_LOAD)
    if (match_substring (string, "NEVER_LOAD"))
      return 1;
  if (flags & SEC_COFF_SHARED_LIBRARY)
    if (match_substring (string, "COFF_SHARED_LIBRARY"))
      return 1;
  if (flags & SEC_IS_COMMON)
    if (match_substring (string, "IS_COMMON"))
      return 1;

  return 0;
}