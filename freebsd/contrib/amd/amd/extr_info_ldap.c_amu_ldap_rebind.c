#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_9__ {scalar_t__ ldap_proto_version; scalar_t__ ldap_cache_seconds; int /*<<< orphan*/  ldap_cache_maxmem; } ;
struct TYPE_8__ {scalar_t__ timestamp; int /*<<< orphan*/ * ldap; TYPE_1__* hostent; TYPE_2__* credentials; } ;
struct TYPE_7__ {int /*<<< orphan*/  who; int /*<<< orphan*/  method; int /*<<< orphan*/  pw; } ;
struct TYPE_6__ {int /*<<< orphan*/  port; int /*<<< orphan*/  host; struct TYPE_6__* next; } ;
typedef  int /*<<< orphan*/  LDAP ;
typedef  TYPE_1__ HE_ENT ;
typedef  TYPE_2__ CR ;
typedef  TYPE_3__ ALD ;

/* Variables and functions */
 scalar_t__ AMD_LDAP_TTL ; 
 int ENOENT ; 
 int /*<<< orphan*/  LDAP_OPT_PROTOCOL_VERSION ; 
 scalar_t__ LDAP_SUCCESS ; 
 scalar_t__ LDAP_VERSION2 ; 
 int /*<<< orphan*/  XLOG_USER ; 
 int /*<<< orphan*/  XLOG_WARNING ; 
 int /*<<< orphan*/  amu_ldap_unbind (int /*<<< orphan*/ *) ; 
 scalar_t__ clocktime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlog (char*,...) ; 
 TYPE_4__ gopt ; 
 scalar_t__ ldap_bind_s (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldap_enable_cache (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldap_set_option (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
amu_ldap_rebind(ALD *a)
{
  LDAP *ld;
  HE_ENT *h;
  CR *c = a->credentials;
  time_t now = clocktime(NULL);
  int try;

  dlog("-> amu_ldap_rebind\n");

  if (a->ldap != NULL) {
    if ((a->timestamp - now) > AMD_LDAP_TTL) {
      dlog("Re-establishing ldap connection\n");
      amu_ldap_unbind(a->ldap);
      a->timestamp = now;
      a->ldap = NULL;
    } else {
      /* Assume all is OK.  If it wasn't we'll be back! */
      dlog("amu_ldap_rebind: timestamp OK\n");
      return (0);
    }
  }

  for (try=0; try<10; try++) {	/* XXX: try up to 10 times (makes sense?) */
    for (h = a->hostent; h != NULL; h = h->next) {
      if ((ld = ldap_open(h->host, h->port)) == NULL) {
	plog(XLOG_WARNING, "Unable to ldap_open to %s:%d\n", h->host, h->port);
	continue;
      }
#if LDAP_VERSION_MAX > LDAP_VERSION2
      /* handle LDAPv3 and heigher, if available and amd.conf-igured */
      if (gopt.ldap_proto_version > LDAP_VERSION2) {
        if (!ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &gopt.ldap_proto_version)) {
          dlog("amu_ldap_rebind: LDAP protocol version set to %ld\n",
	       gopt.ldap_proto_version);
        } else {
          plog(XLOG_WARNING, "Unable to set ldap protocol version to %ld for "
	       "%s:%d\n", gopt.ldap_proto_version, h->host, h->port);
	  continue;
        }
      }
#endif /* LDAP_VERSION_MAX > LDAP_VERSION2 */
      if (ldap_bind_s(ld, c->who, c->pw, c->method) != LDAP_SUCCESS) {
	plog(XLOG_WARNING, "Unable to ldap_bind to %s:%d as %s\n",
	     h->host, h->port, c->who);
	continue;
      }
      if (gopt.ldap_cache_seconds > 0) {
#if defined(HAVE_LDAP_ENABLE_CACHE) && defined(HAVE_EXTERN_LDAP_ENABLE_CACHE)
	ldap_enable_cache(ld, gopt.ldap_cache_seconds, gopt.ldap_cache_maxmem);
#else /* not defined(HAVE_LDAP_ENABLE_CACHE) && defined(HAVE_EXTERN_LDAP_ENABLE_CACHE) */
	plog(XLOG_WARNING, "ldap_enable_cache(%ld) is not available on this system!\n", gopt.ldap_cache_seconds);
#endif /* not defined(HAVE_LDAP_ENABLE_CACHE) && defined(HAVE_EXTERN_LDAP_ENABLE_CACHE) */
      }
      a->ldap = ld;
      a->timestamp = now;
      return (0);
    }
    plog(XLOG_WARNING, "Exhausted list of ldap servers, looping.\n");
  }

  plog(XLOG_USER, "Unable to (re)bind to any ldap hosts\n");
  return (ENOENT);
}