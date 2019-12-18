#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u_long ;
struct nfs_common_args {int flags; int rsize; int wsize; void* retrans; void* timeo; } ;
typedef  int /*<<< orphan*/  mntent_t ;

/* Variables and functions */
 int MNT2_GEN_OPT_RONLY ; 
 int MNT2_NFS_OPT_COMPRESS ; 
 int MNT2_NFS_OPT_INT ; 
 int MNT2_NFS_OPT_INTR ; 
 int MNT2_NFS_OPT_NOACL ; 
 int MNT2_NFS_OPT_NOCONN ; 
 int MNT2_NFS_OPT_NOCTO ; 
 int MNT2_NFS_OPT_NODEVS ; 
 int MNT2_NFS_OPT_NOINT ; 
 int MNT2_NFS_OPT_NOINTR ; 
 int MNT2_NFS_OPT_NONLM ; 
 int MNT2_NFS_OPT_PRIVATE ; 
 int MNT2_NFS_OPT_PROPLIST ; 
 int MNT2_NFS_OPT_RESVPORT ; 
 int MNT2_NFS_OPT_RETRANS ; 
 int MNT2_NFS_OPT_RONLY ; 
 int MNT2_NFS_OPT_RSIZE ; 
 int MNT2_NFS_OPT_SOFT ; 
 int MNT2_NFS_OPT_SPONGY ; 
 int MNT2_NFS_OPT_TCP ; 
 int MNT2_NFS_OPT_TIMEO ; 
 int MNT2_NFS_OPT_WSIZE ; 
 int MNT2_NFS_OPT_XLATECOOKIE ; 
 int /*<<< orphan*/  MNTTAB_OPT_COMPRESS ; 
 int /*<<< orphan*/  MNTTAB_OPT_CONN ; 
 int /*<<< orphan*/  MNTTAB_OPT_INTR ; 
 int /*<<< orphan*/  MNTTAB_OPT_NOACL ; 
 int /*<<< orphan*/  MNTTAB_OPT_NOCONN ; 
 int /*<<< orphan*/  MNTTAB_OPT_NOCTO ; 
 int /*<<< orphan*/  MNTTAB_OPT_NODEVS ; 
 int /*<<< orphan*/  MNTTAB_OPT_NOLOCK ; 
 int /*<<< orphan*/  MNTTAB_OPT_PRIVATE ; 
 int /*<<< orphan*/  MNTTAB_OPT_PROPLIST ; 
 int /*<<< orphan*/  MNTTAB_OPT_RESVPORT ; 
 int /*<<< orphan*/  MNTTAB_OPT_RETRANS ; 
 int /*<<< orphan*/  MNTTAB_OPT_RSIZE ; 
 int /*<<< orphan*/  MNTTAB_OPT_SOFT ; 
 int /*<<< orphan*/  MNTTAB_OPT_SPONGY ; 
 int /*<<< orphan*/  MNTTAB_OPT_TIMEO ; 
 int /*<<< orphan*/  MNTTAB_OPT_WSIZE ; 
 int /*<<< orphan*/  MNTTAB_OPT_XLATECOOKIE ; 
 scalar_t__ NFS_VERSION ; 
 scalar_t__ STREQ (char const*,char*) ; 
 int /*<<< orphan*/  XLOG_USER ; 
 int /*<<< orphan*/  XLOG_WARNING ; 
 int /*<<< orphan*/ * amu_hasmntopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int* flags ; 
 int genflags ; 
 void* hasmntval (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
compute_nfs_common_args(struct nfs_common_args *nap, mntent_t *mntp,
    const char *nfs_proto, u_long nfs_version)
{
#ifdef MNT2_NFS_OPT_TCP
  if (nfs_proto && STREQ(nfs_proto, "tcp"))
    nap->flags |= MNT2_NFS_OPT_TCP;
#endif /* MNT2_NFS_OPT_TCP */

#ifdef MNT2_NFS_OPT_NOCONN
  /* check if user specified to use unconnected or connected sockets */
  if (amu_hasmntopt(mntp, MNTTAB_OPT_NOCONN) != NULL)
    nap->flags |= MNT2_NFS_OPT_NOCONN;
  else if (amu_hasmntopt(mntp, MNTTAB_OPT_CONN) != NULL)
    nap->flags &= ~MNT2_NFS_OPT_NOCONN;
  else {
    /*
     * Some OSs want you to set noconn always.  Some want you to always turn
     * it off.  Others want you to turn it on/off only if NFS V.3 is used.
     * And all of that changes from revision to another.  This is
     * particularly true of OpenBSD, NetBSD, and FreeBSD.  So, rather than
     * attempt to auto-detect this, I'm forced to "fix" it in the individual
     * conf/nfs_prot/nfs_prot_*.h files.
     */
# ifdef USE_UNCONNECTED_NFS_SOCKETS
    if (!(nap->flags & MNT2_NFS_OPT_NOCONN)) {
      nap->flags |= MNT2_NFS_OPT_NOCONN;
      plog(XLOG_WARNING, "noconn option not specified, and was just turned ON (OS override)! (May cause NFS hangs on some systems...)");
    }
# endif /* USE_UNCONNECTED_NFS_SOCKETS */
# ifdef USE_CONNECTED_NFS_SOCKETS
    if (nap->flags & MNT2_NFS_OPT_NOCONN) {
      nap->flags &= ~MNT2_NFS_OPT_NOCONN;
      plog(XLOG_WARNING, "noconn option specified, and was just turned OFF (OS override)! (May cause NFS hangs on some systems...)");
    }
# endif /* USE_CONNECTED_NFS_SOCKETS */
  }
#endif /* MNT2_NFS_OPT_NOCONN */

#ifdef MNT2_NFS_OPT_RESVPORT
# ifdef MNTTAB_OPT_RESVPORT
  if (amu_hasmntopt(mntp, MNTTAB_OPT_RESVPORT) != NULL)
    nap->flags |= MNT2_NFS_OPT_RESVPORT;
# else /* not MNTTAB_OPT_RESVPORT */
  nap->flags |= MNT2_NFS_OPT_RESVPORT;
# endif /* not MNTTAB_OPT_RESVPORT */
#endif /* MNT2_NFS_OPT_RESVPORT */

  nap->rsize = hasmntval(mntp, MNTTAB_OPT_RSIZE);
#ifdef MNT2_NFS_OPT_RSIZE
  if (nap->rsize)
    nap->flags |= MNT2_NFS_OPT_RSIZE;
#endif /* MNT2_NFS_OPT_RSIZE */
  if (nfs_version == NFS_VERSION && nap->rsize > 8192)
    nap->rsize = 8192;

  nap->wsize = hasmntval(mntp, MNTTAB_OPT_WSIZE);
#ifdef MNT2_NFS_OPT_WSIZE
  if (nap->wsize)
    nap->flags |= MNT2_NFS_OPT_WSIZE;
#endif /* MNT2_NFS_OPT_WSIZE */
  if (nfs_version == NFS_VERSION && nap->wsize > 8192)
    nap->wsize = 8192;

  nap->timeo = hasmntval(mntp, MNTTAB_OPT_TIMEO);
#ifdef MNT2_NFS_OPT_TIMEO
  if (nap->timeo)
    nap->flags |= MNT2_NFS_OPT_TIMEO;
#endif /* MNT2_NFS_OPT_TIMEO */

  nap->retrans = hasmntval(mntp, MNTTAB_OPT_RETRANS);
#ifdef MNT2_NFS_OPT_RETRANS
  if (nap->retrans)
    nap->flags |= MNT2_NFS_OPT_RETRANS;
#endif /* MNT2_NFS_OPT_RETRANS */

#ifdef MNT2_NFS_OPT_SOFT
  if (amu_hasmntopt(mntp, MNTTAB_OPT_SOFT) != NULL)
    nap->flags |= MNT2_NFS_OPT_SOFT;
#endif /* MNT2_NFS_OPT_SOFT */

#ifdef MNT2_NFS_OPT_SPONGY
  if (amu_hasmntopt(mntp, MNTTAB_OPT_SPONGY) != NULL) {
    nap->flags |= MNT2_NFS_OPT_SPONGY;
    if (*flags & MNT2_NFS_OPT_SOFT) {
      plog(XLOG_USER, "Mount opts soft and spongy are incompatible - soft ignored");
      nap->flags &= ~MNT2_NFS_OPT_SOFT;
    }
  }
#endif /* MNT2_NFS_OPT_SPONGY */

#if defined(MNT2_GEN_OPT_RONLY) && defined(MNT2_NFS_OPT_RONLY)
  /* Ultrix has separate generic and NFS ro flags */
  if (genflags & MNT2_GEN_OPT_RONLY)
    nap->flags |= MNT2_NFS_OPT_RONLY;
#endif /* defined(MNT2_GEN_OPT_RONLY) && defined(MNT2_NFS_OPT_RONLY) */

#ifdef MNTTAB_OPT_INTR
  if (amu_hasmntopt(mntp, MNTTAB_OPT_INTR) != NULL)
    /*
     * Either turn on the "allow interrupts" option, or
     * turn off the "disallow interrupts" option"
     */
# ifdef MNT2_NFS_OPT_INTR
    nap->flags |= MNT2_NFS_OPT_INTR;
# endif /* MNT2_NFS_OPT_INTR */
# ifdef MNT2_NFS_OPT_NOINTR
    nap->flags &= ~MNT2_NFS_OPT_NOINTR;
# endif /* MNT2_NFS_OPT_NOINTR */
# ifdef MNT2_NFS_OPT_INT
    nap->flags |= MNT2_NFS_OPT_INT;
# endif /* MNT2_NFS_OPT_INT */
# ifdef MNT2_NFS_OPT_NOINT
    nap->flags &= ~MNT2_NFS_OPT_NOINT;
# endif /* MNT2_NFS_OPT_NOINT */
#endif /* MNTTAB_OPT_INTR */

#ifdef MNT2_NFS_OPT_NOACL
  if (amu_hasmntopt(mntp, MNTTAB_OPT_NOACL) != NULL)
    nap->flags |= MNT2_NFS_OPT_NOACL;
#endif /* MNT2_NFS_OPT_NOACL */

#ifdef MNTTAB_OPT_NODEVS
  if (amu_hasmntopt(mntp, MNTTAB_OPT_NODEVS) != NULL)
    nap->flags |= MNT2_NFS_OPT_NODEVS;
#endif /* MNTTAB_OPT_NODEVS */

#ifdef MNTTAB_OPT_COMPRESS
  if (amu_hasmntopt(mntp, MNTTAB_OPT_COMPRESS) != NULL)
    nap->flags |= MNT2_NFS_OPT_COMPRESS;
#endif /* MNTTAB_OPT_COMPRESS */

#ifdef MNTTAB_OPT_PRIVATE	/* mount private, single-client tree */
  if (amu_hasmntopt(mntp, MNTTAB_OPT_PRIVATE) != NULL)
    nap->flags |= MNT2_NFS_OPT_PRIVATE;
#endif /* MNTTAB_OPT_PRIVATE */


#if defined(MNT2_NFS_OPT_NOCTO) && defined(MNTTAB_OPT_NOCTO)
  if (amu_hasmntopt(mntp, MNTTAB_OPT_NOCTO) != NULL)
    nap->flags |= MNT2_NFS_OPT_NOCTO;
#endif /* defined(MNT2_NFS_OPT_NOCTO) && defined(MNTTAB_OPT_NOCTO) */

#if defined(MNT2_NFS_OPT_PROPLIST) && defined(MNTTAB_OPT_PROPLIST)
  if (amu_hasmntopt(mntp, MNTTAB_OPT_PROPLIST) != NULL)
    nap->flags |= MNT2_NFS_OPT_PROPLIST;
#endif /* defined(MNT2_NFS_OPT_PROPLIST) && defined(MNTTAB_OPT_PROPLIST) */

#if defined(MNT2_NFS_OPT_NONLM) && defined(MNTTAB_OPT_NOLOCK)
  if (amu_hasmntopt(mntp, MNTTAB_OPT_NOLOCK) != NULL)
    nap->flags |= MNT2_NFS_OPT_NONLM;
#endif /* defined(MNT2_NFS_OPT_NONLM) && defined(MNTTAB_OPT_NOLOCK) */

#if defined(MNT2_NFS_OPT_XLATECOOKIE) && defined(MNTTAB_OPT_XLATECOOKIE)
  if (amu_hasmntopt(mntp, MNTTAB_OPT_XLATECOOKIE) != NULL)
    nap->flags |= MNT2_NFS_OPT_XLATECOOKIE;
#endif /* defined(MNT2_NFS_OPT_XLATECOOKIE) && defined(MNTTAB_OPT_XLATECOOKIE) */
}