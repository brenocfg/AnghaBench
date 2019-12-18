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
struct pbuf {char* payload; int len; } ;
struct netif {int dummy; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  printf (char*,...) ; 

err_t testnetif_output(struct netif *netif, struct pbuf *p)
{
    int i;
    char *dat = p->payload;

    /* output the packet to stdout */
    printf("\nPacketOut:[");
    for (i=0; i<p->len; i++) {
        printf("%02x", *dat++);
    }
    printf("]\n");

    return ERR_OK;
}