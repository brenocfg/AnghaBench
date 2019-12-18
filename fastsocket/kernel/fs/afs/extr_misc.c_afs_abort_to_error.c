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
typedef  int u32 ;

/* Variables and functions */
 int EACCES ; 
 int EBUSY ; 
 int EDEADLK ; 
 int EDOM ; 
 int EDQUOT ; 
 int EEXIST ; 
 int EFBIG ; 
 int EINVAL ; 
 int EIO ; 
 int EISDIR ; 
 int EKEYEXPIRED ; 
 int EKEYREJECTED ; 
 int EMLINK ; 
 int ENAMETOOLONG ; 
 int ENOENT ; 
 int ENOLCK ; 
 int ENOMEDIUM ; 
 int ENOSPC ; 
 int ENOTDIR ; 
 int ENOTEMPTY ; 
 int ENXIO ; 
 int EPROTO ; 
 int ERANGE ; 
 int EREMOTEIO ; 
 int EROFS ; 
 int EWOULDBLOCK ; 
 int EXDEV ; 
#define  RXKADBADKEY 151 
#define  RXKADBADTICKET 150 
#define  RXKADDATALEN 149 
#define  RXKADEXPIRED 148 
#define  RXKADILLEGALLEVEL 147 
#define  RXKADINCONSISTENCY 146 
#define  RXKADLEVELFAIL 145 
#define  RXKADNOAUTH 144 
#define  RXKADOUTOFSEQUENCE 143 
#define  RXKADPACKETSHORT 142 
#define  RXKADSEALEDINCON 141 
#define  RXKADTICKETLEN 140 
#define  RXKADUNKNOWNKEY 139 
#define  VBUSY 138 
#define  VDISKFULL 137 
#define  VMOVED 136 
#define  VNOSERVICE 135 
#define  VNOVNODE 134 
#define  VNOVOL 133 
#define  VOFFLINE 132 
#define  VONLINE 131 
#define  VOVERQUOTA 130 
#define  VSALVAGE 129 
#define  VVOLEXISTS 128 

int afs_abort_to_error(u32 abort_code)
{
	switch (abort_code) {
	case 13:		return -EACCES;
	case 27:		return -EFBIG;
	case 30:		return -EROFS;
	case VSALVAGE:		return -EIO;
	case VNOVNODE:		return -ENOENT;
	case VNOVOL:		return -ENOMEDIUM;
	case VVOLEXISTS:	return -EEXIST;
	case VNOSERVICE:	return -EIO;
	case VOFFLINE:		return -ENOENT;
	case VONLINE:		return -EEXIST;
	case VDISKFULL:		return -ENOSPC;
	case VOVERQUOTA:	return -EDQUOT;
	case VBUSY:		return -EBUSY;
	case VMOVED:		return -ENXIO;
	case 0x2f6df0a:		return -EWOULDBLOCK;
	case 0x2f6df0c:		return -EACCES;
	case 0x2f6df0f:		return -EBUSY;
	case 0x2f6df10:		return -EEXIST;
	case 0x2f6df11:		return -EXDEV;
	case 0x2f6df13:		return -ENOTDIR;
	case 0x2f6df14:		return -EISDIR;
	case 0x2f6df15:		return -EINVAL;
	case 0x2f6df1a:		return -EFBIG;
	case 0x2f6df1b:		return -ENOSPC;
	case 0x2f6df1d:		return -EROFS;
	case 0x2f6df1e:		return -EMLINK;
	case 0x2f6df20:		return -EDOM;
	case 0x2f6df21:		return -ERANGE;
	case 0x2f6df22:		return -EDEADLK;
	case 0x2f6df23:		return -ENAMETOOLONG;
	case 0x2f6df24:		return -ENOLCK;
	case 0x2f6df26:		return -ENOTEMPTY;
	case 0x2f6df78:		return -EDQUOT;

	case RXKADINCONSISTENCY: return -EPROTO;
	case RXKADPACKETSHORT:	return -EPROTO;
	case RXKADLEVELFAIL:	return -EKEYREJECTED;
	case RXKADTICKETLEN:	return -EKEYREJECTED;
	case RXKADOUTOFSEQUENCE: return -EPROTO;
	case RXKADNOAUTH:	return -EKEYREJECTED;
	case RXKADBADKEY:	return -EKEYREJECTED;
	case RXKADBADTICKET:	return -EKEYREJECTED;
	case RXKADUNKNOWNKEY:	return -EKEYREJECTED;
	case RXKADEXPIRED:	return -EKEYEXPIRED;
	case RXKADSEALEDINCON:	return -EKEYREJECTED;
	case RXKADDATALEN:	return -EKEYREJECTED;
	case RXKADILLEGALLEVEL:	return -EKEYREJECTED;

	default:		return -EREMOTEIO;
	}
}