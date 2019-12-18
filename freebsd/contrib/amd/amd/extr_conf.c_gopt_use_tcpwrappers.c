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
 int /*<<< orphan*/  CFM_USE_TCPWRAPPERS ; 
 scalar_t__ STREQ (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__ gopt ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
gopt_use_tcpwrappers(const char *val)
{
#if defined(HAVE_TCPD_H) && defined(HAVE_LIBWRAP)
  if (STREQ(val, "yes")) {
    gopt.flags |= CFM_USE_TCPWRAPPERS;
    return 0;
  } else if (STREQ(val, "no")) {
    gopt.flags &= ~CFM_USE_TCPWRAPPERS;
    return 0;
  }
#else /* not defined(HAVE_TCPD_H) && defined(HAVE_LIBWRAP) */
    fprintf(stderr, "conf: no tcpd/libwrap support available\n");
    return 1;
#endif /* not defined(HAVE_TCPD_H) && defined(HAVE_LIBWRAP) */

  fprintf(stderr, "conf: unknown value to use_tcpwrappers \"%s\"\n", val);
  return 1;			/* unknown value */
}