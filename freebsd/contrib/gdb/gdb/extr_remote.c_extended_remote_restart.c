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
struct remote_state {int /*<<< orphan*/  remote_packet_size; } ;

/* Variables and functions */
 char* alloca (int /*<<< orphan*/ ) ; 
 struct remote_state* get_remote_state () ; 
 int /*<<< orphan*/  getpkt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putpkt (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
extended_remote_restart (void)
{
  struct remote_state *rs = get_remote_state ();
  char *buf = alloca (rs->remote_packet_size);

  /* Send the restart command; for reasons I don't understand the
     remote side really expects a number after the "R".  */
  buf[0] = 'R';
  sprintf (&buf[1], "%x", 0);
  putpkt (buf);

  /* Now query for status so this looks just like we restarted
     gdbserver from scratch.  */
  putpkt ("?");
  getpkt (buf, (rs->remote_packet_size), 0);
}