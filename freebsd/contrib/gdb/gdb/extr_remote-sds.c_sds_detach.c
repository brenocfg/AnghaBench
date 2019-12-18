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
 int PBUFSIZ ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  pop_target () ; 
 int /*<<< orphan*/  puts_filtered (char*) ; 
 int /*<<< orphan*/  sds_send (char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void
sds_detach (char *args, int from_tty)
{
  char buf[PBUFSIZ];

  if (args)
    error ("Argument given to \"detach\" when remotely debugging.");

#if 0
  /* Tell the remote target to detach.  */
  strcpy (buf, "D");
  sds_send (buf, 1);
#endif

  pop_target ();
  if (from_tty)
    puts_filtered ("Ending remote debugging.\n");
}