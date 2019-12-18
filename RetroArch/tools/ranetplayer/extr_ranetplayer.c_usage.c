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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

void usage()
{
   fprintf(stderr,
      "Use: ranetplayer [options] [ranp file]\n"
      "Options:\n"
      "    -H|--host <address>:  Netplay host. Defaults to localhost.\n"
      "    -P|--port <port>:     Netplay port. Defaults to 55435.\n"
      "    -p|--play <file>:     Play back a recording over netplay.\n"
      "    -r|--record <file>:   Record netplay to a file.\n"
      "    -a|--ahead <frames>:  Number of frames by which to play ahead of the\n"
      "                          server. Tests rewind if negative, catch-up if\n"
      "                          positive.\n"
      "\n");
}