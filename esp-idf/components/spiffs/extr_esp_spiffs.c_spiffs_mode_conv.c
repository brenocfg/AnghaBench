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

/* Variables and functions */
 int O_ACCMODE ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int SPIFFS_O_APPEND ; 
 int SPIFFS_O_CREAT ; 
 int SPIFFS_O_EXCL ; 
 int SPIFFS_O_RDONLY ; 
 int SPIFFS_O_RDWR ; 
 int SPIFFS_O_TRUNC ; 
 int SPIFFS_O_WRONLY ; 

__attribute__((used)) static int spiffs_mode_conv(int m)
{
    int res = 0;
    int acc_mode = m & O_ACCMODE;
    if (acc_mode == O_RDONLY) {
        res |= SPIFFS_O_RDONLY;
    } else if (acc_mode == O_WRONLY) {
        res |= SPIFFS_O_WRONLY;
    } else if (acc_mode == O_RDWR) {
        res |= SPIFFS_O_RDWR;
    }
    if ((m & O_CREAT) && (m & O_EXCL)) {
        res |= SPIFFS_O_CREAT | SPIFFS_O_EXCL;
    } else if ((m & O_CREAT) && (m & O_TRUNC)) {
        res |= SPIFFS_O_CREAT | SPIFFS_O_TRUNC;
    }
    if (m & O_APPEND) {
        res |= SPIFFS_O_CREAT | SPIFFS_O_APPEND;
    }
    return res;
}