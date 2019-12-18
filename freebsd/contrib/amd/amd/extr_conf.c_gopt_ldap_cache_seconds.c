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
struct TYPE_2__ {int /*<<< orphan*/  ldap_cache_seconds; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__ gopt ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strtol (char*,char**,int) ; 

__attribute__((used)) static int
gopt_ldap_cache_seconds(const char *val)
{
#ifdef HAVE_MAP_LDAP
  char *end;

  gopt.ldap_cache_seconds = strtol((char *)val, &end, 10);
  if (end == val) {
    fprintf(stderr, "conf: bad LDAP cache (seconds) option: %s\n",val);
    return 1;
  }
  return 0;
#else /* not HAVE_MAP_LDAP */
  fprintf(stderr, "conf: ldap_cache_seconds option ignored.  No LDAP support available.\n");
  return 1;
#endif /* not HAVE_MAP_LDAP */
}