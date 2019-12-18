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
struct sockaddr_storage {int ss_family; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  ipv6_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int addr_compare(struct sockaddr_storage *x, struct sockaddr_storage *y)
{
        switch (x->ss_family) {
        case AF_INET: {
                struct sockaddr_in *sinx = (struct sockaddr_in *)x;
                struct sockaddr_in *siny = (struct sockaddr_in *)y;
                if (sinx->sin_addr.s_addr != siny->sin_addr.s_addr)
                        return 0;
                if (sinx->sin_port != siny->sin_port)
                        return 0;
                break;
        }
        case AF_INET6: {
                struct sockaddr_in6 *sinx = (struct sockaddr_in6 *)x;
                struct sockaddr_in6 *siny = (struct sockaddr_in6 *)y;
                if (!ipv6_addr_equal(&sinx->sin6_addr, &siny->sin6_addr))
                        return 0;
                if (sinx->sin6_port != siny->sin6_port)
                        return 0;
                break;
        }
        default:
                return 0;
        }
        return 1;
}