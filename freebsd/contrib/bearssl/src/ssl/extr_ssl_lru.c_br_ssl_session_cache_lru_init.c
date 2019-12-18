#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned char* store; size_t store_len; void* root; void* tail; void* head; scalar_t__ init_done; scalar_t__ store_ptr; int /*<<< orphan*/ * vtable; } ;
typedef  TYPE_1__ br_ssl_session_cache_lru ;

/* Variables and functions */
 void* ADDR_NULL ; 
 int /*<<< orphan*/  lru_class ; 

void
br_ssl_session_cache_lru_init(br_ssl_session_cache_lru *cc,
	unsigned char *store, size_t store_len)
{
	cc->vtable = &lru_class;
	cc->store = store;
	cc->store_len = store_len;
	cc->store_ptr = 0;
	cc->init_done = 0;
	cc->head = ADDR_NULL;
	cc->tail = ADDR_NULL;
	cc->root = ADDR_NULL;
}