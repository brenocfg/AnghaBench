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
typedef  int int32_t ;

/* Variables and functions */
#define  APPEND_STATUS_ADDINZIP 130 
#define  APPEND_STATUS_CREATE 129 
#define  APPEND_STATUS_CREATEAFTER 128 
 int MZ_OPEN_MODE_APPEND ; 
 int MZ_OPEN_MODE_CREATE ; 
 int MZ_OPEN_MODE_READ ; 
 int MZ_OPEN_MODE_WRITE ; 

__attribute__((used)) static int32_t zipConvertAppendToStreamMode(int append)
{
    int32_t mode = MZ_OPEN_MODE_WRITE;
    switch (append)
    {
    case APPEND_STATUS_CREATE:
        mode |= MZ_OPEN_MODE_CREATE;
        break;
    case APPEND_STATUS_CREATEAFTER:
        mode |= MZ_OPEN_MODE_CREATE | MZ_OPEN_MODE_APPEND;
        break;
    case APPEND_STATUS_ADDINZIP:
        mode |= MZ_OPEN_MODE_READ | MZ_OPEN_MODE_APPEND;
        break;
    }
    return mode;
}