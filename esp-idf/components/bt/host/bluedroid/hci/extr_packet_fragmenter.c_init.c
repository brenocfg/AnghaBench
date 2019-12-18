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
typedef  int /*<<< orphan*/  packet_fragmenter_callbacks_t ;

/* Variables and functions */
 int /*<<< orphan*/  NUMBER_OF_BUCKETS ; 
 int /*<<< orphan*/  const* callbacks ; 
 int /*<<< orphan*/ * current_fragment_packet ; 
 int /*<<< orphan*/  hash_function_naive ; 
 int /*<<< orphan*/  hash_map_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  partial_packets ; 

__attribute__((used)) static void init(const packet_fragmenter_callbacks_t *result_callbacks)
{
    current_fragment_packet = NULL;
    callbacks = result_callbacks;
    partial_packets = hash_map_new(NUMBER_OF_BUCKETS, hash_function_naive, NULL, NULL, NULL);
}