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
struct ip6q {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add_32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dtom (struct ip6q*) ; 
 int /*<<< orphan*/  ip6q_count ; 
 int /*<<< orphan*/  m_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ip6q_free(struct ip6q *q6)
{
	(void) m_free(dtom(q6));
	atomic_add_32(&ip6q_count, -1);
}