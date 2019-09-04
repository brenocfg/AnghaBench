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
typedef  int action_id_t ;

/* Variables and functions */
#define  CHMOD 154 
#define  CHOWN 153 
#define  CREAT 152 
#define  EXCHANGEDATA 151 
#define  FILLFD 150 
#define  FUNLOCK 149 
#define  HARDLINK 148 
#define  LENGTHEN 147 
#define  LSEEK 146 
#define  LSKEE 145 
#define  MKDIR 144 
#define  MKFIFO 143 
#define  MMAP 142 
#define  NOTHING 141 
#define  OPEN 140 
#define  READ 139 
#define  RENAME 138 
#define  REVOKE 137 
#define  RMDIR 136 
#define  SETXATTR 135 
#define  STAT 134 
#define  SYMLINK 133 
#define  TRUNC 132 
#define  UNLINK 131 
#define  UTIMES 130 
#define  WRITE 129 
#define  WRITEFD 128 

char *
get_action_name(action_id_t a)
{
	switch (a) {
	case CREAT:
		return "CREAT";
	case MKDIR:
		return "MKDIR";
	case READ:
		return "READ";
	case WRITE:
		return "WRITE";
	case WRITEFD:
		return "WRITEFD";
	case FILLFD:
		return "FILLFD";
	case UNLINK:
		return "UNLINK";
	case LSKEE:
		return "LSKEE";
	case RMDIR:
		return "RMDIR";
	case MKFIFO:
		return "MKFIFO";
	case LENGTHEN:
		return "LENGTHEN";
	case TRUNC:
		return "TRUNC";
	case SYMLINK:
		return "SYMLINK";
	case CHMOD:
		return "CHMOD";
	case CHOWN:
		return "CHOWN";
	case EXCHANGEDATA:
		return "EXCHANGEDATA";
	case RENAME:
		return "RENAME";
	case LSEEK:
		return "LSEEK";
	case OPEN:
		return "OPEN";
	case MMAP:
		return "MMAP";
	case NOTHING:
		return "NOTHING";
	case SETXATTR:
		return "SETXATTR";
	case UTIMES:
		return "UTIMES";
	case STAT:
		return "STAT";
	case HARDLINK:
		return "HARDLINK";
	case REVOKE:
		return "REVOKE";
	case FUNLOCK:
		return "FUNLOCK";
	}
	return "Unknown";
}