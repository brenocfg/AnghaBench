#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* h_hostname; int /*<<< orphan*/  h_netswap; int /*<<< orphan*/  h_netroot; } ;
typedef  TYPE_1__ host ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ write_nfsname (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
write_boot_info(FILE *ef, host *hp)
{
  int errors = 0;

  fprintf(ef, "%s\troot=", hp->h_hostname);
  errors += write_nfsname(ef, hp->h_netroot, hp->h_hostname);
  fputs(" swap=", ef);
  errors += write_nfsname(ef, hp->h_netswap, hp->h_hostname);
  fputs("\n", ef);

  return 0;
}