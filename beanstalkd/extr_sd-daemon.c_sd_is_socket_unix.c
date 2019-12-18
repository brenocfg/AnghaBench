#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sun_path; } ;
struct TYPE_4__ {scalar_t__ sa_family; } ;
union sockaddr_union {TYPE_1__ un; TYPE_2__ sa; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sockaddr ;
typedef  int /*<<< orphan*/  sa_family_t ;

/* Variables and functions */
 scalar_t__ AF_UNIX ; 
 int EINVAL ; 
 int errno ; 
 scalar_t__ getsockname (int,TYPE_2__*,int*) ; 
 scalar_t__ memcmp (char const*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memset (union sockaddr_union*,int /*<<< orphan*/ ,int) ; 
 int sd_is_socket_internal (int,int,int) ; 
 size_t strlen (char const*) ; 

int sd_is_socket_unix(int fd, int type, int listening, const char *path, size_t length) {
        union sockaddr_union sockaddr;
        socklen_t l;
        int r;

        if ((r = sd_is_socket_internal(fd, type, listening)) <= 0)
                return r;

        memset(&sockaddr, 0, sizeof(sockaddr));
        l = sizeof(sockaddr);

        if (getsockname(fd, &sockaddr.sa, &l) < 0)
                return -errno;

        if (l < sizeof(sa_family_t))
                return -EINVAL;

        if (sockaddr.sa.sa_family != AF_UNIX)
                return 0;

        if (path) {
                if (length <= 0)
                        length = strlen(path);

                if (length <= 0)
                        /* Unnamed socket */
                        return l == sizeof(sa_family_t);

                if (path[0])
                        /* Normal path socket */
                        return
                                (l >= sizeof(sa_family_t) + length + 1) &&
                                memcmp(path, sockaddr.un.sun_path, length+1) == 0;
                else
                        /* Abstract namespace socket */
                        return
                                (l == sizeof(sa_family_t) + length) &&
                                memcmp(path, sockaddr.un.sun_path, length) == 0;
        }

        return 1;
}