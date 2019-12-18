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
 int /*<<< orphan*/  pop_target () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* target_shortname ; 

__attribute__((used)) static void
st2000_detach (int from_tty)
{
  pop_target ();		/* calls st2000_close to do the real work */
  if (from_tty)
    printf ("Ending remote %s debugging\n", target_shortname);
}