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
struct xfs_mount {scalar_t__ m_rsumip; scalar_t__ m_rbmip; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRELE (scalar_t__) ; 

void
xfs_rtunmount_inodes(
	struct xfs_mount	*mp)
{
	if (mp->m_rbmip)
		IRELE(mp->m_rbmip);
	if (mp->m_rsumip)
		IRELE(mp->m_rsumip);
}