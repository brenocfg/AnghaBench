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
struct necp_client {int /*<<< orphan*/  client_id; } ;

/* Variables and functions */
 int uuid_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
necp_client_id_cmp(struct necp_client *client0, struct necp_client *client1)
{
	return (uuid_compare(client0->client_id, client1->client_id));
}