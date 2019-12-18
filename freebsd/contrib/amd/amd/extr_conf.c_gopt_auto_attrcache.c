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
struct TYPE_2__ {scalar_t__ auto_attrcache; } ;

/* Variables and functions */
 scalar_t__ atoi (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 TYPE_1__ gopt ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
gopt_auto_attrcache(const char *val)
{
  gopt.auto_attrcache = atoi(val);
  if (gopt.auto_attrcache < 0) {
    fprintf(stderr, "conf: bad attrcache value: \"%s\"\n", val);
    return 1;
  }
  return 0;
}