#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  voidp ;
struct in_addr {int dummy; } ;
struct hostent {scalar_t__ h_addrtype; scalar_t__ h_addr; scalar_t__ h_name; } ;
struct TYPE_8__ {int fs_flags; TYPE_1__* fs_ip; int /*<<< orphan*/  fs_host; } ;
typedef  TYPE_2__ fserver ;
struct TYPE_7__ {struct in_addr sin_addr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int FSF_DOWN ; 
 int FSF_FORCE_UNMOUNT ; 
 int FSF_VALID ; 
 int FSF_WANT ; 
 int /*<<< orphan*/  STREQ (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFREE (char*) ; 
 int /*<<< orphan*/  XLOG_WARNING ; 
 int /*<<< orphan*/  flush_nfs_fhandle_cache (TYPE_2__*) ; 
 int /*<<< orphan*/  flush_srvr_nfs_cache (TYPE_2__*) ; 
 struct hostent* gethostbyname (int /*<<< orphan*/ ) ; 
 char* inet_ntoa (struct in_addr) ; 
 int /*<<< orphan*/  map_flush_srvr (TYPE_2__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static void
check_fs_addr_change(fserver *fs)
{
  struct hostent *hp = NULL;
  struct in_addr ia;
  char *old_ipaddr, *new_ipaddr;

  hp = gethostbyname(fs->fs_host);
  if (!hp ||
      hp->h_addrtype != AF_INET ||
      !STREQ((char *) hp->h_name, fs->fs_host) ||
      memcmp((voidp) &fs->fs_ip->sin_addr,
	     (voidp) hp->h_addr,
	     sizeof(fs->fs_ip->sin_addr)) == 0)
    return;
  /* if got here: downed server changed IP address */
  old_ipaddr = xstrdup(inet_ntoa(fs->fs_ip->sin_addr));
  memmove((voidp) &ia, (voidp) hp->h_addr, sizeof(struct in_addr));
  new_ipaddr = inet_ntoa(ia);	/* ntoa uses static buf */
  plog(XLOG_WARNING, "EZK: down fileserver %s changed ip: %s -> %s",
       fs->fs_host, old_ipaddr, new_ipaddr);
  XFREE(old_ipaddr);
  /* copy new IP addr */
  memmove((voidp) &fs->fs_ip->sin_addr,
	  (voidp) hp->h_addr,
	  sizeof(fs->fs_ip->sin_addr));
  /* XXX: do we need to un/set these flags? */
  fs->fs_flags &= ~FSF_DOWN;
  fs->fs_flags |= FSF_VALID | FSF_WANT;
  map_flush_srvr(fs);		/* XXX: a race with flush_srvr_nfs_cache? */
  flush_srvr_nfs_cache(fs);
  fs->fs_flags |= FSF_FORCE_UNMOUNT;

#if 0
  flush_nfs_fhandle_cache(fs);	/* done in caller: nfs_keepalive_timeout */
  /* XXX: need to purge nfs_private so that somehow it will get re-initialized? */
#endif /* 0 */
}