#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int nfs_vers_ping; } ;

/* Variables and functions */
 int atoi (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 TYPE_1__ gopt ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
gopt_nfs_vers_ping(const char *val)
{
  int i = atoi(val);

  if (i == 2 || i == 3 || i == 4) {
    gopt.nfs_vers_ping = i;
    return 0;
  }
  fprintf(stderr, "conf: illegal nfs_vers_ping \"%s\"\n", val);
  return 1;
}