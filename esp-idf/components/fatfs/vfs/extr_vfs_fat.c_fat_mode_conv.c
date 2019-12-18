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
 int FA_CREATE_ALWAYS ; 
 int FA_CREATE_NEW ; 
 int FA_OPEN_ALWAYS ; 
 int FA_OPEN_EXISTING ; 
 int FA_READ ; 
 int FA_WRITE ; 
 int O_ACCMODE ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int O_WRONLY ; 

__attribute__((used)) static int fat_mode_conv(int m)
{
    int res = 0;
    int acc_mode = m & O_ACCMODE;
    if (acc_mode == O_RDONLY) {
        res |= FA_READ;
    } else if (acc_mode == O_WRONLY) {
        res |= FA_WRITE;
    } else if (acc_mode == O_RDWR) {
        res |= FA_READ | FA_WRITE;
    }
    if ((m & O_CREAT) && (m & O_EXCL)) {
        res |= FA_CREATE_NEW;
    } else if ((m & O_CREAT) && (m & O_TRUNC)) {
        res |= FA_CREATE_ALWAYS;
    } else if (m & O_APPEND) {
        res |= FA_OPEN_ALWAYS;
    } else {
        res |= FA_OPEN_EXISTING;
    }
    return res;
}