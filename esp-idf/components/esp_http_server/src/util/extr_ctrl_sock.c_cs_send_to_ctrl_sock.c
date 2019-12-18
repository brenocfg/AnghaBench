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
typedef  int /*<<< orphan*/  to_addr ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  inet_aton (char*,int /*<<< orphan*/ *) ; 
 int sendto (int,void*,unsigned int,int /*<<< orphan*/ ,struct sockaddr*,int) ; 

int cs_send_to_ctrl_sock(int send_fd, int port, void *data, unsigned int data_len)
{
    int ret;
    struct sockaddr_in to_addr;
    to_addr.sin_family = AF_INET;
    to_addr.sin_port = htons(port);
    inet_aton("127.0.0.1", &to_addr.sin_addr);
    ret = sendto(send_fd, data, data_len, 0, (struct sockaddr *)&to_addr, sizeof(to_addr));

    if (ret < 0) {
        return -1;
    }
    return ret;
}