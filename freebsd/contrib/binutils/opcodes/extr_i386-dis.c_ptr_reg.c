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
 int AFLAG ; 
 int PREFIX_ADDR ; 
 scalar_t__ address_mode ; 
 int /*<<< orphan*/  close_char ; 
 int eAX_reg ; 
 scalar_t__ mode_64bit ; 
 char** names16 ; 
 char** names32 ; 
 char** names64 ; 
 int /*<<< orphan*/  oappend (char const*) ; 
 scalar_t__* obufp ; 
 int /*<<< orphan*/  open_char ; 
 int prefixes ; 
 int used_prefixes ; 

__attribute__((used)) static void
ptr_reg (int code, int sizeflag)
{
  const char *s;

  *obufp++ = open_char;
  used_prefixes |= (prefixes & PREFIX_ADDR);
  if (address_mode == mode_64bit)
    {
      if (!(sizeflag & AFLAG))
	s = names32[code - eAX_reg];
      else
	s = names64[code - eAX_reg];
    }
  else if (sizeflag & AFLAG)
    s = names32[code - eAX_reg];
  else
    s = names16[code - eAX_reg];
  oappend (s);
  *obufp++ = close_char;
  *obufp = 0;
}