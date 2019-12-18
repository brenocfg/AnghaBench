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

/* Variables and functions */
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  background_connection_buckets ; 
 scalar_t__ background_connections ; 
 int /*<<< orphan*/  bdaddr_equality_fn ; 
 int /*<<< orphan*/  hash_function_bdaddr ; 
 scalar_t__ hash_map_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_free_func ; 

__attribute__((used)) static void background_connections_lazy_init(void)
{
    if (!background_connections) {
        background_connections = hash_map_new(background_connection_buckets,
                                      hash_function_bdaddr, NULL, osi_free_func, bdaddr_equality_fn);
        assert(background_connections);
    }
}