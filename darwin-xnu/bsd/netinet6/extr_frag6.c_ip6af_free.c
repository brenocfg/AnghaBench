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
struct ip6asfrag {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add_32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dtom (struct ip6asfrag*) ; 
 int /*<<< orphan*/  ip6af_count ; 
 int /*<<< orphan*/  m_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ip6af_free(struct ip6asfrag *af6)
{
	(void) m_free(dtom(af6));
	atomic_add_32(&ip6af_count, -1);
}