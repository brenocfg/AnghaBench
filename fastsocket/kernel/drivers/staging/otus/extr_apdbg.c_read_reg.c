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
struct zdap_ioctl {int dummy; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_ioctl (int,struct ifreq*) ; 

int read_reg(int sock, struct ifreq *req)
{
    struct zdap_ioctl *zdreq = 0;

    if (!set_ioctl(sock, req))
        return -1;

    //zdreq = (struct zdap_ioctl *)req->ifr_data;
    //printf( "reg = %4x, value = %4x\n", zdreq->addr, zdreq->value);

    return 0;
}