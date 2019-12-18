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
typedef  int nfstype ;
typedef  enum vtype { ____Placeholder_vtype } vtype ;

/* Variables and functions */
#define  NFATTRDIR 137 
#define  NFBLK 136 
#define  NFCHR 135 
#define  NFDIR 134 
#define  NFFIFO 133 
#define  NFLNK 132 
#define  NFNAMEDATTR 131 
#define  NFNON 130 
#define  NFREG 129 
#define  NFSOCK 128 
 int NFS_VER2 ; 
 int NFS_VER3 ; 
 int VBLK ; 
 int VCHR ; 
 int VDIR ; 
 int VFIFO ; 
 int VLNK ; 
 int VNON ; 
 int VREG ; 
 int VSOCK ; 

enum vtype
nfstov_type(nfstype nvtype, int nfsvers)
{
	switch (nvtype) {
	case NFNON:
		return VNON;
	case NFREG:
		return VREG;
	case NFDIR:
		return VDIR;
	case NFBLK:
		return VBLK;
	case NFCHR:
		return VCHR;
	case NFLNK:
		return VLNK;
	case NFSOCK:
		if (nfsvers > NFS_VER2)
			return VSOCK;
	case NFFIFO:
		if (nfsvers > NFS_VER2)
			return VFIFO;
	case NFATTRDIR:
		if (nfsvers > NFS_VER3)
			return VDIR;
	case NFNAMEDATTR:
		if (nfsvers > NFS_VER3)
			return VREG;
	default:
		return VNON;
	}
}