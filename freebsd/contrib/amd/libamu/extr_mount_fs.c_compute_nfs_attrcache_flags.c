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
struct nfs_common_args {int acregmin; int acregmax; int acdirmin; int acdirmax; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  mntent_t ;

/* Variables and functions */
 int /*<<< orphan*/  MNT2_NFS_OPT_ACDIRMAX ; 
 int /*<<< orphan*/  MNT2_NFS_OPT_ACDIRMIN ; 
 int /*<<< orphan*/  MNT2_NFS_OPT_ACREGMAX ; 
 int /*<<< orphan*/  MNT2_NFS_OPT_ACREGMIN ; 
 int /*<<< orphan*/  MNT2_NFS_OPT_NOAC ; 
 int /*<<< orphan*/  MNTTAB_OPT_ACDIRMAX ; 
 int /*<<< orphan*/  MNTTAB_OPT_ACDIRMIN ; 
 int /*<<< orphan*/  MNTTAB_OPT_ACREGMAX ; 
 int /*<<< orphan*/  MNTTAB_OPT_ACREGMIN ; 
 int /*<<< orphan*/  MNTTAB_OPT_ACTIMEO ; 
 int /*<<< orphan*/  MNTTAB_OPT_NOAC ; 
 int /*<<< orphan*/ * amu_hasmntopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hasmntvalerr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
compute_nfs_attrcache_flags(struct nfs_common_args *nap, mntent_t *mntp)
{
  int acval = 0;
  int err_acval = 1;		/* 1 means we found no 'actimeo' value */
#if defined(HAVE_NFS_ARGS_T_ACREGMIN) || defined(HAVE_NFS_ARGS_T_ACREGMAX) || defined(HAVE_NFS_ARGS_T_ACDIRMIN) || defined(HAVE_NFS_ARGS_T_ACDIRMAX)
  int err_acrdmm;		/* for ac{reg,dir}{min,max} */
#endif /* HAVE_NFS_ARGS_T_AC{REG,DIR}{MIN,MAX} */

  /************************************************************************/
  /***	ATTRIBUTE CACHES						***/
  /************************************************************************/
  /*
   * acval is set to 0 at the top of the function.  If actimeo mount option
   * exists and defined in mntopts, then its acval is set to it.
   * If the value is non-zero, then we set all attribute cache fields to it.
   * If acval is zero, it means it was never defined in mntopts or the
   * actimeo mount option does not exist, in which case we check for
   * individual mount options per attribute cache.
   * Regardless of the value of acval, mount flags are set based directly
   * on the values of the attribute caches.
   */
#ifdef MNTTAB_OPT_ACTIMEO
  err_acval = hasmntvalerr(mntp, MNTTAB_OPT_ACTIMEO, &acval);	/* attr cache timeout (sec) */
#endif /* MNTTAB_OPT_ACTIMEO */

  /*** acregmin ***/
#ifdef HAVE_NFS_ARGS_T_ACREGMIN
  err_acrdmm = 1;		/* 1 means we found no acregmin value */
  if (!err_acval) {
    nap->acregmin = acval;	/* min ac timeout for reg files (sec) */
  } else {
# ifdef MNTTAB_OPT_ACREGMIN
    int tmp;
    err_acrdmm = hasmntvalerr(mntp, MNTTAB_OPT_ACREGMIN, &tmp);
    nap->acregmin = tmp;
# else /* not MNTTAB_OPT_ACREGMIN */
    nap->acregmin = 0;
# endif /* not MNTTAB_OPT_ACREGMIN */
  }
  /* set this flag iff we changed acregmin (possibly to zero) */
# ifdef MNT2_NFS_OPT_ACREGMIN
  if (!err_acval || !err_acrdmm)
    nap->flags |= MNT2_NFS_OPT_ACREGMIN;
# endif /* MNT2_NFS_OPT_ACREGMIN */
#endif /* HAVE_NFS_ARGS_T_ACREGMIN */

  /*** acregmax ***/
#ifdef HAVE_NFS_ARGS_T_ACREGMAX
  err_acrdmm = 1;		/* 1 means we found no acregmax value */
  if (!err_acval) {
    nap->acregmax = acval;	/* max ac timeout for reg files (sec) */
  } else {
# ifdef MNTTAB_OPT_ACREGMAX
    int tmp;
    err_acrdmm = hasmntvalerr(mntp, MNTTAB_OPT_ACREGMAX, &tmp);
    nap->acregmax = tmp;
# else /* not MNTTAB_OPT_ACREGMAX */
    nap->acregmax = 0;
# endif /* not MNTTAB_OPT_ACREGMAX */
  }
  /* set this flag iff we changed acregmax (possibly to zero) */
# ifdef MNT2_NFS_OPT_ACREGMAX
  if (!err_acval || !err_acrdmm)
    nap->flags |= MNT2_NFS_OPT_ACREGMAX;
# endif /* MNT2_NFS_OPT_ACREGMAX */
#endif /* HAVE_NFS_ARGS_T_ACREGMAX */

  /*** acdirmin ***/
#ifdef HAVE_NFS_ARGS_T_ACDIRMIN
  err_acrdmm = 1;		/* 1 means we found no acdirmin value */
  if (!err_acval) {
    nap->acdirmin = acval;	/* min ac timeout for dirs (sec) */
  } else {
# ifdef MNTTAB_OPT_ACDIRMIN
    int tmp;
    err_acrdmm = hasmntvalerr(mntp, MNTTAB_OPT_ACDIRMIN, &tmp);
    nap->acdirmin = tmp;
# else /* not MNTTAB_OPT_ACDIRMIN */
    nap->acdirmin = 0;
# endif /* not MNTTAB_OPT_ACDIRMIN */
  }
  /* set this flag iff we changed acdirmin (possibly to zero) */
# ifdef MNT2_NFS_OPT_ACDIRMIN
  if (!err_acval || !err_acrdmm)
    nap->flags |= MNT2_NFS_OPT_ACDIRMIN;
# endif /* MNT2_NFS_OPT_ACDIRMIN */
#endif /* HAVE_NFS_ARGS_T_ACDIRMIN */

  /*** acdirmax ***/
#ifdef HAVE_NFS_ARGS_T_ACDIRMAX
  err_acrdmm = 1;		/* 1 means we found no acdirmax value */
  if (!err_acval) {
    nap->acdirmax = acval;	/* max ac timeout for dirs (sec) */
  } else {
# ifdef MNTTAB_OPT_ACDIRMAX
    int tmp;
    err_acrdmm = hasmntvalerr(mntp, MNTTAB_OPT_ACDIRMAX, &tmp);
    nap->acdirmax = tmp;
# else /* not MNTTAB_OPT_ACDIRMAX */
    nap->acdirmax = 0;
# endif /* not MNTTAB_OPT_ACDIRMAX */
  }
  /* set this flag iff we changed acdirmax (possibly to zero) */
# ifdef MNT2_NFS_OPT_ACDIRMAX
  if (!err_acval || !err_acrdmm)
    nap->flags |= MNT2_NFS_OPT_ACDIRMAX;
# endif /* MNT2_NFS_OPT_ACDIRMAX */
#endif /* HAVE_NFS_ARGS_T_ACDIRMAX */


  /* don't cache attributes */
#if defined(MNTTAB_OPT_NOAC) && defined(MNT2_NFS_OPT_NOAC)
  if (amu_hasmntopt(mntp, MNTTAB_OPT_NOAC) != NULL)
    nap->flags |= MNT2_NFS_OPT_NOAC;
#endif /* defined(MNTTAB_OPT_NOAC) && defined(MNT2_NFS_OPT_NOAC) */
}