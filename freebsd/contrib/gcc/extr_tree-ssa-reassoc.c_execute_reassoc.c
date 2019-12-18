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
 int /*<<< orphan*/  do_reassoc () ; 
 int /*<<< orphan*/  fini_reassoc () ; 
 int /*<<< orphan*/  init_reassoc () ; 
 int /*<<< orphan*/  repropagate_negates () ; 

__attribute__((used)) static unsigned int
execute_reassoc (void)
{
  init_reassoc ();

  do_reassoc ();
  repropagate_negates ();

  fini_reassoc ();
  return 0;
}