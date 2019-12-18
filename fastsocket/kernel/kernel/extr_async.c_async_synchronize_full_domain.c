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
struct async_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  async_synchronize_cookie_domain (int /*<<< orphan*/ ,struct async_domain*) ; 
 int /*<<< orphan*/  next_cookie ; 

void async_synchronize_full_domain(struct async_domain *domain)
{
	async_synchronize_cookie_domain(next_cookie, domain);
}