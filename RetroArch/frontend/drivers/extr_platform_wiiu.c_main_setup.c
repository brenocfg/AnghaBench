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
 int /*<<< orphan*/  ProcUIInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SaveCallback ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_logging () ; 
 int /*<<< orphan*/  init_network () ; 
 int /*<<< orphan*/  init_pad_libraries () ; 
 int /*<<< orphan*/  setup_os_exceptions () ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  verbosity_enable () ; 

__attribute__((used)) static void main_setup(void)
{
   setup_os_exceptions();
   ProcUIInit(&SaveCallback);
   init_network();
   init_logging();
   init_pad_libraries();
   verbosity_enable();
   fflush(stdout);
}