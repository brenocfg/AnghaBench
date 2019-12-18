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
struct TYPE_5__ {scalar_t__ root; scalar_t__ store; } ;
typedef  TYPE_1__ br_ssl_session_cache_lru ;

/* Variables and functions */
 scalar_t__ ADDR_NULL ; 
 int /*<<< orphan*/  SESSION_ID_LEN ; 
 scalar_t__ SESSION_ID_OFF ; 
 scalar_t__ TREE_LEFT_OFF ; 
 scalar_t__ TREE_RIGHT_OFF ; 
 scalar_t__ get_left (TYPE_1__*,scalar_t__) ; 
 scalar_t__ get_right (TYPE_1__*,scalar_t__) ; 
 int memcmp (unsigned char const*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
find_node(br_ssl_session_cache_lru *cc, const unsigned char *id,
	uint32_t *addr_link)
{
	uint32_t x, y;

	x = cc->root;
	y = ADDR_NULL;
	while (x != ADDR_NULL) {
		int r;

		r = memcmp(id, cc->store + x + SESSION_ID_OFF, SESSION_ID_LEN);
		if (r < 0) {
			y = x + TREE_LEFT_OFF;
			x = get_left(cc, x);
		} else if (r == 0) {
			if (addr_link != NULL) {
				*addr_link = y;
			}
			return x;
		} else {
			y = x + TREE_RIGHT_OFF;
			x = get_right(cc, x);
		}
	}
	if (addr_link != NULL) {
		*addr_link = y;
	}
	return ADDR_NULL;
}