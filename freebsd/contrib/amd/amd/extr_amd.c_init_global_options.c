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
struct utsname {void* machine; } ;
struct amu_global_options {int dummy; } ;
struct TYPE_3__ {char* auto_dir; char* pid_file; int* amfs_auto_retrans; int* amfs_auto_timeo; char* hesiod_base; int ldap_cache_maxmem; int ldap_proto_version; int /*<<< orphan*/ * nis_domain; scalar_t__ ldap_cache_seconds; int /*<<< orphan*/ * ldap_hostports; int /*<<< orphan*/ * ldap_base; int /*<<< orphan*/  flags; int /*<<< orphan*/  map_reload_interval; int /*<<< orphan*/  am_timeo_w; int /*<<< orphan*/  am_timeo; int /*<<< orphan*/ * sub_domain; int /*<<< orphan*/  op_sys_vendor; int /*<<< orphan*/  op_sys_full; int /*<<< orphan*/  op_sys_ver; int /*<<< orphan*/  op_sys; int /*<<< orphan*/ * logfile; void* karch; int /*<<< orphan*/  exec_map_timeout; int /*<<< orphan*/ * cluster; scalar_t__ auto_attrcache; void* arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMFS_EXEC_MAP_TIMEOUT ; 
 int AMU_TYPE_MAX ; 
 int /*<<< orphan*/  AM_TTL ; 
 int /*<<< orphan*/  AM_TTL_W ; 
 int /*<<< orphan*/  CFM_DEFAULT_FLAGS ; 
 void* HOST_ARCH ; 
 int /*<<< orphan*/  HOST_OS ; 
 int /*<<< orphan*/  HOST_OS_NAME ; 
 int /*<<< orphan*/  HOST_OS_VERSION ; 
 int /*<<< orphan*/  HOST_VENDOR ; 
 int /*<<< orphan*/  ONE_HOUR ; 
 TYPE_1__ gopt ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ uname (struct utsname*) ; 

__attribute__((used)) static void
init_global_options(void)
{
#if defined(HAVE_SYS_UTSNAME_H) && defined(HAVE_UNAME)
  static struct utsname un;
#endif /* defined(HAVE_SYS_UTSNAME_H) && defined(HAVE_UNAME) */
  int i;

  memset(&gopt, 0, sizeof(struct amu_global_options));

  /* name of current architecture */
  gopt.arch = HOST_ARCH;

  /* automounter temp dir */
  gopt.auto_dir = "/.amd_mnt";

  /* toplevel attribute cache timeout */
  gopt.auto_attrcache = 0;

  /* cluster name */
  gopt.cluster = NULL;

  /* executable map timeout */
  gopt.exec_map_timeout = AMFS_EXEC_MAP_TIMEOUT;

  /*
   * kernel architecture: this you must get from uname() if possible.
   */
#if defined(HAVE_SYS_UTSNAME_H) && defined(HAVE_UNAME)
  if (uname(&un) >= 0)
    gopt.karch = un.machine;
  else
#endif /* defined(HAVE_SYS_UTSNAME_H) && defined(HAVE_UNAME) */
    gopt.karch = HOST_ARCH;

  /* amd log file */
  gopt.logfile = NULL;

  /* operating system name */
  gopt.op_sys = HOST_OS_NAME;

  /* OS version */
  gopt.op_sys_ver = HOST_OS_VERSION;

  /* full OS name and version */
  gopt.op_sys_full = HOST_OS;

  /* OS version */
  gopt.op_sys_vendor = HOST_VENDOR;

  /* pid file */
  gopt.pid_file = "/dev/stdout";

  /* local domain */
  gopt.sub_domain = NULL;

  /* reset NFS (and toplvl) retransmit counter and retry interval */
  for (i=0; i<AMU_TYPE_MAX; ++i) {
    gopt.amfs_auto_retrans[i] = -1; /* -1 means "never set before" */
    gopt.amfs_auto_timeo[i] = -1; /* -1 means "never set before" */
  }

  /* cache duration */
  gopt.am_timeo = AM_TTL;

  /* dismount interval */
  gopt.am_timeo_w = AM_TTL_W;

  /* map reload intervl */
  gopt.map_reload_interval = ONE_HOUR;

  /*
   * various CFM_* flags that are on by default.
   */
  gopt.flags = CFM_DEFAULT_FLAGS;

#ifdef HAVE_MAP_HESIOD
  /* Hesiod rhs zone */
  gopt.hesiod_base = "automount";
#endif /* HAVE_MAP_HESIOD */

#ifdef HAVE_MAP_LDAP
  /* LDAP base */
  gopt.ldap_base = NULL;

  /* LDAP host ports */
  gopt.ldap_hostports = NULL;

  /* LDAP cache */
  gopt.ldap_cache_seconds = 0;
  gopt.ldap_cache_maxmem = 131072;

  /* LDAP protocol version */
  gopt.ldap_proto_version = 2;
#endif /* HAVE_MAP_LDAP */

#ifdef HAVE_MAP_NIS
  /* YP domain name */
  gopt.nis_domain = NULL;
#endif /* HAVE_MAP_NIS */
}