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
typedef  int I_32 ;

/* Variables and functions */
#define  EACCES 137 
#define  EBADF 136 
#define  EEXIST 135 
#define  EFBIG 134 
#define  ELOOP 133 
#define  ENAMETOOLONG 132 
#define  ENOENT 131 
#define  ENOSPC 130 
#define  ENOTDIR 129 
#define  EPERM 128 
 int HYPORT_ERROR_FILE_BADF ; 
 int HYPORT_ERROR_FILE_DISKFULL ; 
 int HYPORT_ERROR_FILE_EXIST ; 
 int HYPORT_ERROR_FILE_LOOP ; 
 int HYPORT_ERROR_FILE_NAMETOOLONG ; 
 int HYPORT_ERROR_FILE_NOENT ; 
 int HYPORT_ERROR_FILE_NOPERMISSION ; 
 int HYPORT_ERROR_FILE_NOTDIR ; 
 int HYPORT_ERROR_FILE_OPFAILED ; 

__attribute__((used)) static I_32 findError (I_32 errorCode)
{
    switch (errorCode)
    {
        case EACCES:
        case EPERM:
            return HYPORT_ERROR_FILE_NOPERMISSION;
        case ENAMETOOLONG:
            return HYPORT_ERROR_FILE_NAMETOOLONG;
        case ENOENT:
            return HYPORT_ERROR_FILE_NOENT;
        case ENOTDIR:
            return HYPORT_ERROR_FILE_NOTDIR;
        case ELOOP:
            return HYPORT_ERROR_FILE_LOOP;
            
        case EBADF:
            return HYPORT_ERROR_FILE_BADF;
        case EEXIST:
            return HYPORT_ERROR_FILE_EXIST;
        case ENOSPC:
        case EFBIG:
            return HYPORT_ERROR_FILE_DISKFULL;
        default:
            return HYPORT_ERROR_FILE_OPFAILED;
    }
}