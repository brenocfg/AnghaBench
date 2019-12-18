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
struct ipath_devdata {int ipath_tidtemplate; int ipath_ibmaxlen; long long ipath_tidinvalid; } ;

/* Variables and functions */
 long long INFINIPATH_RT_BUFSIZE_MASK ; 
 long long INFINIPATH_RT_BUFSIZE_SHIFT ; 
 long long INFINIPATH_RT_VALID ; 

__attribute__((used)) static void ipath_ht_tidtemplate(struct ipath_devdata *dd)
{
	dd->ipath_tidtemplate = dd->ipath_ibmaxlen >> 2;
	dd->ipath_tidtemplate <<= INFINIPATH_RT_BUFSIZE_SHIFT;
	dd->ipath_tidtemplate |= INFINIPATH_RT_VALID;

	/*
	 * work around chip errata bug 7358, by marking invalid tids
	 * as having max length
	 */
	dd->ipath_tidinvalid = (-1LL & INFINIPATH_RT_BUFSIZE_MASK) <<
		INFINIPATH_RT_BUFSIZE_SHIFT;
}