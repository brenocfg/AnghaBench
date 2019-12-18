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
struct necp_client {scalar_t__ reference_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  NECP_CLIENT_ASSERT_LOCKED (struct necp_client*) ; 

__attribute__((used)) static void
necp_client_retain_locked(struct necp_client *client)
{
	NECP_CLIENT_ASSERT_LOCKED(client);

	client->reference_count++;
	ASSERT(client->reference_count != 0);
}