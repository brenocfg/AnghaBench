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
typedef  int ssize_t ;

/* Variables and functions */
 int read (int,char*,int) ; 

int anetRead(int fd, char *buf, int count)
{
    ssize_t nread, totlen = 0;
    while(totlen != count) {
        nread = read(fd,buf,count-totlen);
        if (nread == 0) return totlen;
        if (nread == -1) return -1;
        totlen += nread;
        buf += nread;
    }
    return totlen;
}