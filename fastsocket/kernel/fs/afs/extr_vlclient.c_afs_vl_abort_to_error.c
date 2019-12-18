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
#define  AFSVL_BADENTRY 155 
#define  AFSVL_BADINDEX 154 
#define  AFSVL_BADNAME 153 
#define  AFSVL_BADPARTITION 152 
#define  AFSVL_BADREFCOUNT 151 
#define  AFSVL_BADRELLOCKTYPE 150 
#define  AFSVL_BADSERVER 149 
#define  AFSVL_BADSERVERFLAG 148 
#define  AFSVL_BADVOLIDBUMP 147 
#define  AFSVL_BADVOLOPER 146 
#define  AFSVL_BADVOLTYPE 145 
#define  AFSVL_CREATEFAIL 144 
#define  AFSVL_DUPREPSERVER 143 
#define  AFSVL_EMPTY 142 
#define  AFSVL_ENTDELETED 141 
#define  AFSVL_ENTRYLOCKED 140 
#define  AFSVL_IDALREADYHASHED 139 
#define  AFSVL_IDEXIST 138 
#define  AFSVL_IO 137 
#define  AFSVL_NAMEEXIST 136 
#define  AFSVL_NOENT 135 
#define  AFSVL_NOMEM 134 
#define  AFSVL_NOREPSERVER 133 
#define  AFSVL_PERM 132 
#define  AFSVL_REPSFULL 131 
#define  AFSVL_RERELEASE 130 
#define  AFSVL_RWNOTFOUND 129 
#define  AFSVL_SIZEEXCEEDED 128 
 int EACCES ; 
 int EBADRQC ; 
 int EBUSY ; 
 int EEXIST ; 
 int EFBIG ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEDIUM ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  _enter (char*,int) ; 
 int afs_abort_to_error (int) ; 

__attribute__((used)) static int afs_vl_abort_to_error(u32 abort_code)
{
	_enter("%u", abort_code);

	switch (abort_code) {
	case AFSVL_IDEXIST:		return -EEXIST;
	case AFSVL_IO:			return -EREMOTEIO;
	case AFSVL_NAMEEXIST:		return -EEXIST;
	case AFSVL_CREATEFAIL:		return -EREMOTEIO;
	case AFSVL_NOENT:		return -ENOMEDIUM;
	case AFSVL_EMPTY:		return -ENOMEDIUM;
	case AFSVL_ENTDELETED:		return -ENOMEDIUM;
	case AFSVL_BADNAME:		return -EINVAL;
	case AFSVL_BADINDEX:		return -EINVAL;
	case AFSVL_BADVOLTYPE:		return -EINVAL;
	case AFSVL_BADSERVER:		return -EINVAL;
	case AFSVL_BADPARTITION:	return -EINVAL;
	case AFSVL_REPSFULL:		return -EFBIG;
	case AFSVL_NOREPSERVER:		return -ENOENT;
	case AFSVL_DUPREPSERVER:	return -EEXIST;
	case AFSVL_RWNOTFOUND:		return -ENOENT;
	case AFSVL_BADREFCOUNT:		return -EINVAL;
	case AFSVL_SIZEEXCEEDED:	return -EINVAL;
	case AFSVL_BADENTRY:		return -EINVAL;
	case AFSVL_BADVOLIDBUMP:	return -EINVAL;
	case AFSVL_IDALREADYHASHED:	return -EINVAL;
	case AFSVL_ENTRYLOCKED:		return -EBUSY;
	case AFSVL_BADVOLOPER:		return -EBADRQC;
	case AFSVL_BADRELLOCKTYPE:	return -EINVAL;
	case AFSVL_RERELEASE:		return -EREMOTEIO;
	case AFSVL_BADSERVERFLAG:	return -EINVAL;
	case AFSVL_PERM:		return -EACCES;
	case AFSVL_NOMEM:		return -EREMOTEIO;
	default:
		return afs_abort_to_error(abort_code);
	}
}