#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct in_addr {void* s_addr; } ;
struct TYPE_7__ {void* s_addr; } ;

/* Variables and functions */
 int IFXNAMSIZ ; 
 int /*<<< orphan*/  SADB_ADD ; 
 int /*<<< orphan*/  T_ASSERT_GE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_ATEND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_LOG (char*,char*) ; 
 int /*<<< orphan*/  cleanup_tunsock ; 
 int /*<<< orphan*/  create_sa (char*,int /*<<< orphan*/ ,int,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  create_tunsock (int,int,int) ; 
 TYPE_1__ g_addr1 ; 
 TYPE_1__ g_addr2 ; 
 scalar_t__ g_is_ipsec_test ; 
 int /*<<< orphan*/  g_tunsock ; 
 scalar_t__ getpid () ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  ifnet_add_addr4 (char*,TYPE_1__*,struct in_addr*,TYPE_1__*) ; 
 int /*<<< orphan*/  tunsock_get_ifname (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
setup_tunsock(void)
{
	T_ASSERT_GE(g_tunsock = create_tunsock(true, false, true), 0, NULL);
	T_ATEND(cleanup_tunsock);

	char ifname[IFXNAMSIZ];
	tunsock_get_ifname(g_tunsock, ifname);

	T_LOG("Created interface %s", ifname);

	uint32_t ifaddr = (10 << 24) | ((unsigned)getpid()&0xffff) << 8 | 160;
	struct in_addr mask;
	g_addr1.s_addr = htonl(ifaddr);
	g_addr2.s_addr = htonl(ifaddr+1);
	mask.s_addr = htonl(0xffffffff);

	ifnet_add_addr4(ifname, &g_addr1, &mask, &g_addr2);

	if (g_is_ipsec_test) {
		create_sa(ifname, SADB_ADD, 12345, &g_addr1, &g_addr2);
		create_sa(ifname, SADB_ADD, 12346, &g_addr2, &g_addr1);
	}
}