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
 int ANET_ERR ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  anetSetError (char*,char*,int /*<<< orphan*/ ) ; 
 int anetSetReuseAddr (char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int socket (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int anetCreateSocket(char *err, int domain) {
    int s;
    if ((s = socket(domain, SOCK_STREAM, 0)) == -1) {
        anetSetError(err, "creating socket: %s", strerror(errno));
        return ANET_ERR;
    }

    /* Make sure connection-intensive things like the redis benchmark
     * will be able to close/open sockets a zillion of times */
    if (anetSetReuseAddr(err,s) == ANET_ERR) {
        close(s);
        return ANET_ERR;
    }
    return s;
}