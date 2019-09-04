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
struct socket {int dummy; } ;
struct in_addr {int dummy; } ;
struct sockaddr_in {struct in_addr sin_addr; } ;
struct ifaliasreq {int /*<<< orphan*/  ifra_broadaddr; int /*<<< orphan*/  ifra_mask; int /*<<< orphan*/  ifra_addr; int /*<<< orphan*/  ifra_name; } ;
typedef  int /*<<< orphan*/  ifra ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCAIFADDR ; 
 struct sockaddr_in blank_sin ; 
 int /*<<< orphan*/  bzero (struct ifaliasreq*,int) ; 
 int /*<<< orphan*/  current_proc () ; 
 int ifioctl (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int
inet_aifaddr(struct socket * so, const char * name,
	     const struct in_addr * addr,
	     const struct in_addr * mask,
	     const struct in_addr * broadcast)
{
    struct ifaliasreq	ifra;

    bzero(&ifra, sizeof(ifra));
    strlcpy(ifra.ifra_name, name, sizeof(ifra.ifra_name));
    if (addr) {
	*((struct sockaddr_in *)(void *)&ifra.ifra_addr) = blank_sin;
	((struct sockaddr_in *)(void *)&ifra.ifra_addr)->sin_addr = *addr;
    }
    if (mask) {
	*((struct sockaddr_in *)(void *)&ifra.ifra_mask) = blank_sin;
	((struct sockaddr_in *)(void *)&ifra.ifra_mask)->sin_addr = *mask;
    }
    if (broadcast) {
	*((struct sockaddr_in *)(void *)&ifra.ifra_broadaddr) = blank_sin;
	((struct sockaddr_in *)(void *)&ifra.ifra_broadaddr)->sin_addr = *broadcast;
    }
    return (ifioctl(so, SIOCAIFADDR, (caddr_t)&ifra, current_proc()));
}