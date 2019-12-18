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
struct sockaddr_in {int dummy; } ;
struct mcast_data {struct sockaddr_in* mcast_addr; } ;

/* Variables and functions */
 int net_sendto (int,void*,int,struct sockaddr_in*,int) ; 

int mcast_user_write(int fd, void *buf, int len, struct mcast_data *pri)
{
	struct sockaddr_in *data_addr = pri->mcast_addr;

	return net_sendto(fd, buf, len, data_addr, sizeof(*data_addr));
}