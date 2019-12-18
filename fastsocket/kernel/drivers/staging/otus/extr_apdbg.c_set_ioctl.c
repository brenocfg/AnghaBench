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
struct ifreq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZDAPIOCTL ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 char* prgname ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

int set_ioctl(int sock, struct ifreq *req)
{
    if (ioctl(sock, ZDAPIOCTL, req) < 0) {
        fprintf(stderr, "%s: ioctl(SIOCGIFMAP): %s\n",
                prgname, strerror(errno));
        return -1;
    }

    return 0;
}