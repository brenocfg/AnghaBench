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
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFM_AUTOFS_USE_LOFS ; 
 scalar_t__ STREQ (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 TYPE_1__ gopt ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
gopt_autofs_use_lofs(const char *val)
{
  if (STREQ(val, "yes")) {
    gopt.flags |= CFM_AUTOFS_USE_LOFS;
    return 0;
  } else if (STREQ(val, "no")) {
    gopt.flags &= ~CFM_AUTOFS_USE_LOFS;
    return 0;
  }

  fprintf(stderr, "conf: unknown value to autofs_use_lofs \"%s\"\n", val);
  return 1;			/* unknown value */
}