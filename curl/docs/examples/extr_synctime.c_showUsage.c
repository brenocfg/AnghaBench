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

void showUsage(void)
{
  fprintf(stderr, "SYNCTIME: Synchronising computer clock with time server"
          " using HTTP protocol.\n");
  fprintf(stderr, "Usage   : SYNCTIME [Option]\n");
  fprintf(stderr, "Options :\n");
  fprintf(stderr, " --server=WEBSERVER        Use this time server instead"
          " of default.\n");
  fprintf(stderr, " --showall                 Show all HTTP header.\n");
  fprintf(stderr, " --synctime                Synchronising computer clock"
          " with time server.\n");
  fprintf(stderr, " --proxy-user=USER[:PASS]  Set proxy username and"
          " password.\n");
  fprintf(stderr, " --proxy=HOST[:PORT]       Use HTTP proxy on given"
          " port.\n");
  fprintf(stderr, " --help                    Print this help.\n");
  fprintf(stderr, "\n");
  return;
}