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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  ino_t ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  FSID_DEV 135 
#define  FSID_ENCODE_DEV 134 
#define  FSID_MAJOR_MINOR 133 
#define  FSID_NUM 132 
#define  FSID_UUID16 131 
#define  FSID_UUID16_INUM 130 
#define  FSID_UUID4_INUM 129 
#define  FSID_UUID8 128 
 int MAJOR (int /*<<< orphan*/ ) ; 
 int MINOR (int /*<<< orphan*/ ) ; 
 int htonl (int) ; 
 int ino_t_to_u32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,unsigned char*,int) ; 
 int new_encode_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mk_fsid(int vers, u32 *fsidv, dev_t dev, ino_t ino,
			   u32 fsid, unsigned char *uuid)
{
	u32 *up;
	switch(vers) {
	case FSID_DEV:
		fsidv[0] = htonl((MAJOR(dev)<<16) |
				 MINOR(dev));
		fsidv[1] = ino_t_to_u32(ino);
		break;
	case FSID_NUM:
		fsidv[0] = fsid;
		break;
	case FSID_MAJOR_MINOR:
		fsidv[0] = htonl(MAJOR(dev));
		fsidv[1] = htonl(MINOR(dev));
		fsidv[2] = ino_t_to_u32(ino);
		break;

	case FSID_ENCODE_DEV:
		fsidv[0] = new_encode_dev(dev);
		fsidv[1] = ino_t_to_u32(ino);
		break;

	case FSID_UUID4_INUM:
		/* 4 byte fsid and inode number */
		up = (u32*)uuid;
		fsidv[0] = ino_t_to_u32(ino);
		fsidv[1] = up[0] ^ up[1] ^ up[2] ^ up[3];
		break;

	case FSID_UUID8:
		/* 8 byte fsid  */
		up = (u32*)uuid;
		fsidv[0] = up[0] ^ up[2];
		fsidv[1] = up[1] ^ up[3];
		break;

	case FSID_UUID16:
		/* 16 byte fsid - NFSv3+ only */
		memcpy(fsidv, uuid, 16);
		break;

	case FSID_UUID16_INUM:
		/* 8 byte inode and 16 byte fsid */
		*(u64*)fsidv = (u64)ino;
		memcpy(fsidv+2, uuid, 16);
		break;
	default: BUG();
	}
}