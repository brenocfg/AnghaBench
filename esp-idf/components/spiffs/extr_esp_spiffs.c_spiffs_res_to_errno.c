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
typedef  int s32_t ;

/* Variables and functions */
 int EBADF ; 
 int EEXIST ; 
 int EIO ; 
 int ENAMETOOLONG ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENOSPC ; 
 int ENOTSUP ; 
 int EROFS ; 
#define  SPIFFS_ERR_BAD_DESCRIPTOR 141 
#define  SPIFFS_ERR_DELETED 140 
#define  SPIFFS_ERR_FILE_DELETED 139 
#define  SPIFFS_ERR_FILE_EXISTS 138 
#define  SPIFFS_ERR_FULL 137 
#define  SPIFFS_ERR_MOUNTED 136 
#define  SPIFFS_ERR_NAME_TOO_LONG 135 
#define  SPIFFS_ERR_NOT_A_FILE 134 
#define  SPIFFS_ERR_NOT_A_FS 133 
#define  SPIFFS_ERR_NOT_FOUND 132 
#define  SPIFFS_ERR_NOT_MOUNTED 131 
#define  SPIFFS_ERR_RO_ABORTED_OPERATION 130 
#define  SPIFFS_ERR_RO_NOT_IMPL 129 
#define  SPIFFS_OK 128 

__attribute__((used)) static int spiffs_res_to_errno(s32_t fr)
{
    switch(fr) {
    case SPIFFS_OK :
        return 0;
    case SPIFFS_ERR_NOT_MOUNTED :
        return ENODEV;
    case SPIFFS_ERR_NOT_A_FS :
        return ENODEV;
    case SPIFFS_ERR_FULL :
        return ENOSPC;
    case SPIFFS_ERR_BAD_DESCRIPTOR :
        return EBADF;
    case SPIFFS_ERR_MOUNTED :
        return EEXIST;
    case SPIFFS_ERR_FILE_EXISTS :
        return EEXIST;
    case SPIFFS_ERR_NOT_FOUND :
        return ENOENT;
    case SPIFFS_ERR_NOT_A_FILE :
        return ENOENT;
    case SPIFFS_ERR_DELETED :
        return ENOENT;
    case SPIFFS_ERR_FILE_DELETED :
        return ENOENT;
    case SPIFFS_ERR_NAME_TOO_LONG :
        return ENAMETOOLONG;
    case SPIFFS_ERR_RO_NOT_IMPL :
        return EROFS;
    case SPIFFS_ERR_RO_ABORTED_OPERATION :
        return EROFS;
    default :
        return EIO;
    }
    return ENOTSUP;
}