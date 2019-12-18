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
struct TCP_Server_Info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_credits_field (struct TCP_Server_Info*) ; 
 int wait_for_free_credits (struct TCP_Server_Info*,int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
wait_for_free_request(struct TCP_Server_Info *server, const int optype)
{
	return wait_for_free_credits(server, optype, get_credits_field(server));
}