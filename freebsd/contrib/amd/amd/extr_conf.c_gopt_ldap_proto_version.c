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
struct TYPE_2__ {int ldap_proto_version; } ;

/* Variables and functions */
#define  LDAP_VERSION2 130 
#define  LDAP_VERSION3 129 
#define  LDAP_VERSION4 128 
 int LDAP_VERSION_MAX ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__ gopt ; 
 int /*<<< orphan*/  stderr ; 
 int strtol (char*,char**,int) ; 

__attribute__((used)) static int
gopt_ldap_proto_version(const char *val)
{
#ifdef HAVE_MAP_LDAP
  char *end;

  gopt.ldap_proto_version = strtol((char *)val, &end, 10);
  if (end == val) {
    fprintf(stderr, "conf: bad ldap_proto_version option: %s\n",val);
    return 1;
  }

  if (gopt.ldap_proto_version < 0 || gopt.ldap_proto_version > LDAP_VERSION_MAX) {
    fprintf(stderr, "conf: bad ldap_proto_version option value: %s\n",val);
    return 1;
  }
  switch (gopt.ldap_proto_version) {
    /* XXX: what about LDAP_VERSION1? */
  case LDAP_VERSION2:
#ifdef LDAP_VERSION3
  case LDAP_VERSION3:
#endif /* LDAP_VERSION3 */
#ifdef LDAP_VERSION4
  case LDAP_VERSION4:
#endif /* LDAP_VERSION4 */
    break;
  default:
    fprintf(stderr, "conf: unsupported ldap_proto_version option value: %s\n",val);
    return 1;
  }
  return 0;
#else /* not HAVE_MAP_LDAP */
  fprintf(stderr, "conf: ldap_proto_version option ignored.  No LDAP support available.\n");
  return 1;
#endif /* not HAVE_MAP_LDAP */
}