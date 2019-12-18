#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  addr; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ network_address ;

/* Variables and functions */
 int /*<<< orphan*/  S (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_string_assign_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* network_address_new () ; 

network_address *network_address_copy(network_address *dst, network_address *src) {
	if (!dst) dst = network_address_new();

	dst->len = src->len;
	dst->addr = src->addr;
	g_string_assign_len(dst->name, S(src->name));

	return dst;
}