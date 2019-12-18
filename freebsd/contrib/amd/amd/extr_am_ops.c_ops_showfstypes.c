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

/* Variables and functions */
 char* MNTTAB_TYPE_AUTOFS ; 
 char* MNTTAB_TYPE_CACHEFS ; 
 char* MNTTAB_TYPE_CDFS ; 
 char* MNTTAB_TYPE_CFS ; 
 char* MNTTAB_TYPE_EFS ; 
 char* MNTTAB_TYPE_LOFS ; 
 char* MNTTAB_TYPE_MFS ; 
 char* MNTTAB_TYPE_NFS ; 
 char* MNTTAB_TYPE_NULLFS ; 
 char* MNTTAB_TYPE_PCFS ; 
 char* MNTTAB_TYPE_TFS ; 
 char* MNTTAB_TYPE_TMPFS ; 
 char* MNTTAB_TYPE_UFS ; 
 char* MNTTAB_TYPE_UMAPFS ; 
 char* MNTTAB_TYPE_UNIONFS ; 
 char* MNTTAB_TYPE_XFS ; 
 int /*<<< orphan*/  ops_show1 (char*,size_t,int*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  xstrlcat (char*,char*,size_t) ; 

void
ops_showfstypes(char *buf, size_t l)
{
  int linesize = 0;

  buf[0] = '\0';

#ifdef MNTTAB_TYPE_AUTOFS
  ops_show1(buf, l, &linesize, MNTTAB_TYPE_AUTOFS);
#endif /* MNTTAB_TYPE_AUTOFS */

#ifdef MNTTAB_TYPE_CACHEFS
  ops_show1(buf, l, &linesize, MNTTAB_TYPE_CACHEFS);
#endif /* MNTTAB_TYPE_CACHEFS */

#ifdef MNTTAB_TYPE_CDFS
  ops_show1(buf, l, &linesize, MNTTAB_TYPE_CDFS);
#endif /* MNTTAB_TYPE_CDFS */

#ifdef MNTTAB_TYPE_CFS
  ops_show1(buf, l, &linesize, MNTTAB_TYPE_CFS);
#endif /* MNTTAB_TYPE_CFS */

#ifdef MNTTAB_TYPE_LOFS
  ops_show1(buf, l, &linesize, MNTTAB_TYPE_LOFS);
#endif /* MNTTAB_TYPE_LOFS */

#ifdef MNTTAB_TYPE_EFS
  ops_show1(buf, l, &linesize, MNTTAB_TYPE_EFS);
#endif /* MNTTAB_TYPE_EFS */

#ifdef MNTTAB_TYPE_MFS
  ops_show1(buf, l, &linesize, MNTTAB_TYPE_MFS);
#endif /* MNTTAB_TYPE_MFS */

#ifdef MNTTAB_TYPE_NFS
  ops_show1(buf, l, &linesize, MNTTAB_TYPE_NFS);
#endif /* MNTTAB_TYPE_NFS */

#ifdef MNTTAB_TYPE_NFS3
  ops_show1(buf, l, &linesize, "nfs3"); /* always hard-code as nfs3 */
#endif /* MNTTAB_TYPE_NFS3 */

#ifdef MNTTAB_TYPE_NULLFS
  ops_show1(buf, l, &linesize, MNTTAB_TYPE_NULLFS);
#endif /* MNTTAB_TYPE_NULLFS */

#ifdef MNTTAB_TYPE_PCFS
  ops_show1(buf, l, &linesize, MNTTAB_TYPE_PCFS);
#endif /* MNTTAB_TYPE_PCFS */

#ifdef MNTTAB_TYPE_TFS
  ops_show1(buf, l, &linesize, MNTTAB_TYPE_TFS);
#endif /* MNTTAB_TYPE_TFS */

#ifdef MNTTAB_TYPE_TMPFS
  ops_show1(buf, l, &linesize, MNTTAB_TYPE_TMPFS);
#endif /* MNTTAB_TYPE_TMPFS */

#ifdef MNTTAB_TYPE_UFS
  ops_show1(buf, l, &linesize, MNTTAB_TYPE_UFS);
#endif /* MNTTAB_TYPE_UFS */

#ifdef MNTTAB_TYPE_UMAPFS
  ops_show1(buf, l, &linesize, MNTTAB_TYPE_UMAPFS);
#endif /* MNTTAB_TYPE_UMAPFS */

#ifdef MNTTAB_TYPE_UNIONFS
  ops_show1(buf, l, &linesize, MNTTAB_TYPE_UNIONFS);
#endif /* MNTTAB_TYPE_UNIONFS */

#ifdef MNTTAB_TYPE_XFS
  ops_show1(buf, l, &linesize, MNTTAB_TYPE_XFS);
#endif /* MNTTAB_TYPE_XFS */

  /* terminate with a period, newline, and NULL */
  if (buf[strlen(buf)-1] == '\n')
    buf[strlen(buf) - 4] = '\0';
  else
    buf[strlen(buf) - 2] = '\0';
  xstrlcat(buf, ".\n", l);
}