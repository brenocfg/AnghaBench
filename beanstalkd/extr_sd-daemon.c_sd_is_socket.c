#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int sa_family; } ;
union sockaddr_union {TYPE_1__ sa; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sockaddr ;
typedef  int /*<<< orphan*/  sa_family_t ;

/* Variables and functions */
 int EINVAL ; 
 int errno ; 
 scalar_t__ getsockname (int,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  memset (union sockaddr_union*,int /*<<< orphan*/ ,int) ; 
 int sd_is_socket_internal (int,int,int) ; 

int sd_is_socket(int fd, int family, int type, int listening) {
        int r;

        if (family < 0)
                return -EINVAL;

        if ((r = sd_is_socket_internal(fd, type, listening)) <= 0)
                return r;

        if (family > 0) {
                union sockaddr_union sockaddr;
                socklen_t l;

                memset(&sockaddr, 0, sizeof(sockaddr));
                l = sizeof(sockaddr);

                if (getsockname(fd, &sockaddr.sa, &l) < 0)
                        return -errno;

                if (l < sizeof(sa_family_t))
                        return -EINVAL;

                return sockaddr.sa.sa_family == family;
        }

        return 1;
}