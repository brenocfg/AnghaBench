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
struct rxrpc_conn_bundle {scalar_t__ key; scalar_t__ service_id; } ;
struct key {int dummy; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */

__attribute__((used)) static inline
int rxrpc_cmp_bundle(const struct rxrpc_conn_bundle *bundle,
		     struct key *key, __be16 service_id)
{
	return (bundle->service_id - service_id) ?:
		((unsigned long) bundle->key - (unsigned long) key);
}