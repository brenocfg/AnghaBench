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
 int /*<<< orphan*/  MNTTAB_OPT_ACTDIRMAX ; 
 int /*<<< orphan*/  MNTTAB_OPT_ACTDIRMIN ; 
 int /*<<< orphan*/  MNTTAB_OPT_ACTIMEO ; 
 int /*<<< orphan*/  MNTTAB_OPT_ACTREGMAX ; 
 int /*<<< orphan*/  MNTTAB_OPT_ACTREGMIN ; 
 int /*<<< orphan*/  MNTTAB_OPT_NOAC ; 
 TYPE_1__ gopt ; 
 int /*<<< orphan*/  xsnprintf (char*,size_t,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  xstrlcat (char*,char*,size_t) ; 

__attribute__((used)) static void
set_auto_attrcache_timeout(char *preopts, char *opts, size_t l)
{

#ifdef MNTTAB_OPT_NOAC
  /*
   * Don't cache attributes - they are changing under the kernel's feet.
   * For example, IRIX5.2 will dispense with nfs lookup calls and hand stale
   * filehandles to getattr unless we disable attribute caching on the
   * automount points.
   */
  if (gopt.auto_attrcache == 0) {
    xsnprintf(preopts, l, ",%s", MNTTAB_OPT_NOAC);
    xstrlcat(opts, preopts, l);
  }
#endif /* MNTTAB_OPT_NOAC */

  /*
   * XXX: note that setting these to 0 in the past resulted in an error on
   * some systems, which is why it's better to use "noac" if possible.  For
   * now, we're setting everything possible, but if this will cause trouble,
   * then we'll have to condition the remainder of this on OPT_NOAC.
   */
#ifdef MNTTAB_OPT_ACTIMEO
  xsnprintf(preopts, l, ",%s=%d", MNTTAB_OPT_ACTIMEO, gopt.auto_attrcache);
  xstrlcat(opts, preopts, l);
#else /* MNTTAB_OPT_ACTIMEO */
# ifdef MNTTAB_OPT_ACDIRMIN
  xsnprintf(preopts, l, ",%s=%d", MNTTAB_OPT_ACTDIRMIN, gopt.auto_attrcache);
  xstrlcat(opts, preopts, l);
# endif /* MNTTAB_OPT_ACDIRMIN */
# ifdef MNTTAB_OPT_ACDIRMAX
  xsnprintf(preopts, l, ",%s=%d", MNTTAB_OPT_ACTDIRMAX, gopt.auto_attrcache);
  xstrlcat(opts, preopts, l);
# endif /* MNTTAB_OPT_ACDIRMAX */
# ifdef MNTTAB_OPT_ACREGMIN
  xsnprintf(preopts, l, ",%s=%d", MNTTAB_OPT_ACTREGMIN, gopt.auto_attrcache);
  xstrlcat(opts, preopts, l);
# endif /* MNTTAB_OPT_ACREGMIN */
# ifdef MNTTAB_OPT_ACREGMAX
  xsnprintf(preopts, l, ",%s=%d", MNTTAB_OPT_ACTREGMAX, gopt.auto_attrcache);
  xstrlcat(opts, preopts, l);
# endif /* MNTTAB_OPT_ACREGMAX */
#endif /* MNTTAB_OPT_ACTIMEO */
}