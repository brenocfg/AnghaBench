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

int read_mem(int sock, struct ifreq *req)
{
    struct zdap_ioctl *zdreq = 0;
    int i;

    if (!set_ioctl(sock, req))
        return -1;

    /*zdreq = (struct zdap_ioctl *)req->ifr_data;
    printf( "dump mem from %x, length = %x\n", zdreq->addr, zdreq->value);

    for (i=0; i<zdreq->value; i++) {
        printf("%02x", zdreq->data[i]);
        printf(" ");

        if ((i>0) && ((i+1)%16 == 0))
            printf("\n");
    }*/

    return 0;
}