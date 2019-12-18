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
struct TYPE_2__ {int /*<<< orphan*/  nfs_proto; } ;

/* Variables and functions */
 scalar_t__ STREQ (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 TYPE_1__ gopt ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static int
gopt_nfs_proto(const char *val)
{
  if (STREQ(val, "udp") || STREQ(val, "tcp")) {
    gopt.nfs_proto = xstrdup(val);
    return 0;
  }
  fprintf(stderr, "conf: illegal nfs_proto \"%s\"\n", val);
  return 1;
}