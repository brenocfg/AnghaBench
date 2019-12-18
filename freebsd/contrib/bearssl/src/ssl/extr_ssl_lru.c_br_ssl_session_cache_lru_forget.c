#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__ store; int /*<<< orphan*/  init_done; } ;
typedef  TYPE_1__ br_ssl_session_cache_lru ;

/* Variables and functions */
 scalar_t__ ADDR_NULL ; 
 int SESSION_ID_LEN ; 
 scalar_t__ VERSION_OFF ; 
 int /*<<< orphan*/  br_enc16be (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ find_node (TYPE_1__*,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mask_id (TYPE_1__*,unsigned char const*,unsigned char*) ; 

void br_ssl_session_cache_lru_forget(
	br_ssl_session_cache_lru *cc, const unsigned char *id)
{
	unsigned char mid[SESSION_ID_LEN];
	uint32_t addr;

	/*
	 * If the cache is not initialised yet, then it is empty, and
	 * there is nothing to forget.
	 */
	if (!cc->init_done) {
		return;
	}

	/*
	 * Look for the node in the tree. If found, the entry is marked
	 * as "disabled"; it will be reused in due course, as it ages
	 * through the list.
	 *
	 * We do not go through the complex moves of actually releasing
	 * the entry right away because explicitly forgetting sessions
	 * should be a rare event, meant mostly for testing purposes,
	 * so this is not worth the extra code size.
	 */
	mask_id(cc, id, mid);
	addr = find_node(cc, mid, NULL);
	if (addr != ADDR_NULL) {
		br_enc16be(cc->store + addr + VERSION_OFF, 0);
	}
}