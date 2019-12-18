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
 scalar_t__ __mf_get_state () ; 
 int /*<<< orphan*/  __mf_set_state (scalar_t__) ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ reentrant ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  write (int,char const*,int) ; 

__attribute__((used)) static void
begin_recursion_protect1 (const char *pf)
{
  if (__mf_get_state () == reentrant)
    {
      write (2, "mf: erroneous reentrancy detected in `", 38);
      write (2, pf, strlen(pf));
      write (2, "'\n", 2); \
      abort ();
    }
  __mf_set_state (reentrant);
}