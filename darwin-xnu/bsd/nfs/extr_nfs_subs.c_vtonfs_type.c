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
typedef  int /*<<< orphan*/  nfstype ;
typedef  enum vtype { ____Placeholder_vtype } vtype ;

/* Variables and functions */
 int /*<<< orphan*/  NFBLK ; 
 int /*<<< orphan*/  NFCHR ; 
 int /*<<< orphan*/  NFDIR ; 
 int /*<<< orphan*/  NFFIFO ; 
 int /*<<< orphan*/  NFLNK ; 
 int /*<<< orphan*/  NFNON ; 
 int /*<<< orphan*/  NFREG ; 
 int /*<<< orphan*/  NFSOCK ; 
 int NFS_VER2 ; 
#define  VBAD 138 
#define  VBLK 137 
#define  VCHR 136 
#define  VCPLX 135 
#define  VDIR 134 
#define  VFIFO 133 
#define  VLNK 132 
#define  VNON 131 
#define  VREG 130 
#define  VSOCK 129 
#define  VSTR 128 

nfstype
vtonfs_type(enum vtype vtype, int nfsvers)
{
	switch (vtype) {
	case VNON:
		return NFNON;
	case VREG:
		return NFREG;
	case VDIR:
		return NFDIR;
	case VBLK:
		return NFBLK;
	case VCHR:
		return NFCHR;
	case VLNK:
		return NFLNK;
	case VSOCK:
		if (nfsvers > NFS_VER2)
			return NFSOCK;
	case VFIFO:
		if (nfsvers > NFS_VER2)
			return NFFIFO;
	case VBAD:
	case VSTR:
	case VCPLX:
	default:
		return NFNON;
	}
}