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
 int CONSTRAINT_LEN (char const,char const*) ; 
 int DEFAULT_CONSTRAINT_LEN (char const,char const*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static int
constraint_len (const char *p, int genoutput_default_constraint_len)
{
  /* Check that we still match defaults.h .  First we do a generation-time
     check that fails if the value is not the expected one...  */
  gcc_assert (DEFAULT_CONSTRAINT_LEN (*p, p) == 1);
  /* And now a compile-time check that should give a diagnostic if the
     definition doesn't exactly match.  */
#define DEFAULT_CONSTRAINT_LEN(C,STR) 1
  /* Now re-define DEFAULT_CONSTRAINT_LEN so that we can verify it is
     being used.  */
#undef DEFAULT_CONSTRAINT_LEN
#define DEFAULT_CONSTRAINT_LEN(C,STR) \
  ((C) != *p || STR != p ? -1 : genoutput_default_constraint_len)
  return CONSTRAINT_LEN (*p, p);
  /* And set it back.  */
#undef DEFAULT_CONSTRAINT_LEN
#define DEFAULT_CONSTRAINT_LEN(C,STR) 1
}