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
typedef  int u_int32_t ;
typedef  int u_int16_t ;
struct TYPE_4__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  addr6; } ;
struct tcp_cache_key_src {scalar_t__ af; TYPE_2__ faddr; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  addr6; } ;
struct tcp_cache_key {TYPE_1__ tck_dst; scalar_t__ tck_family; int /*<<< orphan*/  tck_src; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  bzero (struct tcp_cache_key*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int net_flowhash (struct tcp_cache_key*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_cache_hash_seed ; 
 int /*<<< orphan*/  tcp_cache_hash_src (struct tcp_cache_key_src*,int /*<<< orphan*/ *) ; 
 int tcp_cache_size ; 

__attribute__((used)) static u_int16_t tcp_cache_hash(struct tcp_cache_key_src *tcks, struct tcp_cache_key *key)
{
	u_int32_t hash;

	bzero(key, sizeof(struct tcp_cache_key));

	tcp_cache_hash_src(tcks, &key->tck_src);

	if (tcks->af == AF_INET6) {
		key->tck_family = AF_INET6;
		memcpy(&key->tck_dst.addr6, &tcks->faddr.addr6,
		    sizeof(struct in6_addr));
	} else {
		key->tck_family = AF_INET;
		memcpy(&key->tck_dst.addr, &tcks->faddr.addr,
		    sizeof(struct in_addr));
	}

	hash = net_flowhash(key, sizeof(struct tcp_cache_key),
	    tcp_cache_hash_seed);

	return (hash & (tcp_cache_size - 1));
}