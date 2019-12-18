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
typedef  scalar_t__ u32 ;
typedef  enum vers_op { ____Placeholder_vers_op } vers_op ;

/* Variables and functions */
#define  NFSD_AVAIL 131 
#define  NFSD_CLEAR 130 
#define  NFSD_SET 129 
 scalar_t__ NFSD_SUPPORTED_MINOR_VERSION ; 
#define  NFSD_TEST 128 
 scalar_t__ nfsd_supported_minorversion ; 

int nfsd_minorversion(u32 minorversion, enum vers_op change)
{
	if (minorversion > NFSD_SUPPORTED_MINOR_VERSION)
		return -1;
	switch(change) {
	case NFSD_SET:
		nfsd_supported_minorversion = minorversion;
		break;
	case NFSD_CLEAR:
		if (minorversion == 0)
			return -1;
		nfsd_supported_minorversion = minorversion - 1;
		break;
	case NFSD_TEST:
		return minorversion <= nfsd_supported_minorversion;
	case NFSD_AVAIL:
		return minorversion <= NFSD_SUPPORTED_MINOR_VERSION;
	}
	return 0;
}