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
typedef  int* uuid_t ;

/* Variables and functions */
 int /*<<< orphan*/  uuid_generate_random (int*) ; 

__attribute__((used)) static inline void
necp_generate_client_id(uuid_t client_id, bool is_flow)
{
	uuid_generate_random(client_id);

	if (is_flow) {
		client_id[9] |= 0x01;
	} else {
		client_id[9] &= ~0x01;
	}
}