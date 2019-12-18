#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct TYPE_8__ {int sa_family; } ;
struct TYPE_7__ {char* sun_path; } ;
struct TYPE_11__ {TYPE_4__ ipv6; TYPE_3__ ipv4; TYPE_2__ common; TYPE_1__ un; } ;
struct TYPE_12__ {TYPE_5__ addr; int /*<<< orphan*/  name; } ;
typedef  TYPE_6__ network_address ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  gsize ;
typedef  int /*<<< orphan*/  dst_addr ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_UNIX 128 
 int /*<<< orphan*/  C (char*) ; 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  S (int /*<<< orphan*/ ) ; 
 char* inet_ntoa (int /*<<< orphan*/ ) ; 
 char* inet_ntop (int,int /*<<< orphan*/ *,char*,int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ luaL_checkself (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ strleq (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proxy_address_get(lua_State *L) {
	network_address *addr = *(network_address **)luaL_checkself(L);
	gsize keysize = 0;
	const char *key = luaL_checklstring(L, 2, &keysize);

	if (strleq(key, keysize, C("type"))) {
		lua_pushinteger(L, addr->addr.common.sa_family);
	} else if (strleq(key, keysize, C("name"))) {
		lua_pushlstring(L, S(addr->name));
	} else if (strleq(key, keysize, C("address"))) {
#ifdef HAVE_INET_NTOP
		char dst_addr[INET6_ADDRSTRLEN];
#endif
		const char *str = NULL;

		switch (addr->addr.common.sa_family) {
		case AF_INET:
			str = inet_ntoa(addr->addr.ipv4.sin_addr);
			if (!str) {
				/* it shouldn't really fail, how about logging it ? */ 
			}
			break;
#ifdef HAVE_INET_NTOP
		case AF_INET6:
			str = inet_ntop(addr->addr.common.sa_family, &addr->addr.ipv6.sin6_addr, dst_addr, sizeof(dst_addr));
			if (!str) {
				/* it shouldn't really fail, how about logging it ? */ 
			}
			break;
#endif
#ifndef WIN32
		case AF_UNIX:
			str = addr->addr.un.sun_path;
			break;
#endif
		default:
			break;
		}

		if (NULL == str) {
			lua_pushnil(L);
		} else {
			lua_pushstring(L, str);
		}
	} else if (strleq(key, keysize, C("port"))) {
		switch (addr->addr.common.sa_family) {
		case AF_INET:
			lua_pushinteger(L, ntohs(addr->addr.ipv4.sin_port));
			break;
		case AF_INET6:
			lua_pushinteger(L, ntohs(addr->addr.ipv6.sin6_port));
			break;
		default:
			lua_pushnil(L);
			break;
		}
	} else {
		lua_pushnil(L);
	}

	return 1;
}