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
typedef  int FRESULT ;

/* Variables and functions */
 int EACCES ; 
 int EBADF ; 
 int EEXIST ; 
 int EINTR ; 
 int EINVAL ; 
 int EIO ; 
 int ENFILE ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENOTSUP ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
#define  FR_DENIED 147 
#define  FR_DISK_ERR 146 
#define  FR_EXIST 145 
#define  FR_INT_ERR 144 
#define  FR_INVALID_DRIVE 143 
#define  FR_INVALID_NAME 142 
#define  FR_INVALID_OBJECT 141 
#define  FR_INVALID_PARAMETER 140 
#define  FR_LOCKED 139 
#define  FR_MKFS_ABORTED 138 
#define  FR_NOT_ENABLED 137 
#define  FR_NOT_ENOUGH_CORE 136 
#define  FR_NOT_READY 135 
#define  FR_NO_FILE 134 
#define  FR_NO_FILESYSTEM 133 
#define  FR_NO_PATH 132 
#define  FR_OK 131 
#define  FR_TIMEOUT 130 
#define  FR_TOO_MANY_OPEN_FILES 129 
#define  FR_WRITE_PROTECTED 128 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int fresult_to_errno(FRESULT fr)
{
    switch(fr) {
        case FR_DISK_ERR:       return EIO;
        case FR_INT_ERR:
            assert(0 && "fatfs internal error");
            return EIO;
        case FR_NOT_READY:      return ENODEV;
        case FR_NO_FILE:        return ENOENT;
        case FR_NO_PATH:        return ENOENT;
        case FR_INVALID_NAME:   return EINVAL;
        case FR_DENIED:         return EACCES;
        case FR_EXIST:          return EEXIST;
        case FR_INVALID_OBJECT: return EBADF;
        case FR_WRITE_PROTECTED: return EACCES;
        case FR_INVALID_DRIVE:  return ENXIO;
        case FR_NOT_ENABLED:    return ENODEV;
        case FR_NO_FILESYSTEM:  return ENODEV;
        case FR_MKFS_ABORTED:   return EINTR;
        case FR_TIMEOUT:        return ETIMEDOUT;
        case FR_LOCKED:         return EACCES;
        case FR_NOT_ENOUGH_CORE: return ENOMEM;
        case FR_TOO_MANY_OPEN_FILES: return ENFILE;
        case FR_INVALID_PARAMETER: return EINVAL;
        case FR_OK: return 0;
    }
    assert(0 && "unhandled FRESULT");
    return ENOTSUP;
}