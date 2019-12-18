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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_family; TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 size_t const INET_ADDRSTRLEN ; 
 scalar_t__ in4_pton (char const*,size_t const,int /*<<< orphan*/ *,char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct sockaddr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static size_t rpc_pton4(const char *buf, const size_t buflen,
			struct sockaddr *sap, const size_t salen)
{
	struct sockaddr_in *sin = (struct sockaddr_in *)sap;
	u8 *addr = (u8 *)&sin->sin_addr.s_addr;

	if (buflen > INET_ADDRSTRLEN || salen < sizeof(struct sockaddr_in))
		return 0;

	memset(sap, 0, sizeof(struct sockaddr_in));

	if (in4_pton(buf, buflen, addr, '\0', NULL) == 0)
		return 0;

	sin->sin_family = AF_INET;
	return sizeof(struct sockaddr_in);;
}