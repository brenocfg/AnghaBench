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
typedef  int /*<<< orphan*/  tv ;
struct timeval {long long tv_sec; long long tv_usec; } ;

/* Variables and functions */
 int ANET_ERR ; 
 int ANET_OK ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_SNDTIMEO ; 
 int /*<<< orphan*/  anetSetError (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int anetSendTimeout(char *err, int fd, long long ms) {
    struct timeval tv;

    tv.tv_sec = ms/1000;
    tv.tv_usec = (ms%1000)*1000;
    if (setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv)) == -1) {
        anetSetError(err, "setsockopt SO_SNDTIMEO: %s", strerror(errno));
        return ANET_ERR;
    }
    return ANET_OK;
}