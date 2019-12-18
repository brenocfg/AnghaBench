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
 int PREFIX_CS ; 
 int PREFIX_DS ; 
 int PREFIX_ES ; 
 int PREFIX_FS ; 
 int PREFIX_GS ; 
 int PREFIX_SS ; 
 size_t intel_syntax ; 
 int /*<<< orphan*/  oappend (char*) ; 
 int prefixes ; 
 int used_prefixes ; 

__attribute__((used)) static void
append_seg (void)
{
  if (prefixes & PREFIX_CS)
    {
      used_prefixes |= PREFIX_CS;
      oappend (&"%cs:"[intel_syntax]);
    }
  if (prefixes & PREFIX_DS)
    {
      used_prefixes |= PREFIX_DS;
      oappend (&"%ds:"[intel_syntax]);
    }
  if (prefixes & PREFIX_SS)
    {
      used_prefixes |= PREFIX_SS;
      oappend (&"%ss:"[intel_syntax]);
    }
  if (prefixes & PREFIX_ES)
    {
      used_prefixes |= PREFIX_ES;
      oappend (&"%es:"[intel_syntax]);
    }
  if (prefixes & PREFIX_FS)
    {
      used_prefixes |= PREFIX_FS;
      oappend (&"%fs:"[intel_syntax]);
    }
  if (prefixes & PREFIX_GS)
    {
      used_prefixes |= PREFIX_GS;
      oappend (&"%gs:"[intel_syntax]);
    }
}