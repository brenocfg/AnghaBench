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
struct nd6_prproxy_soltgt {int /*<<< orphan*/  soltgt_key; } ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static __inline int
soltgt_cmp(const struct nd6_prproxy_soltgt *a,
    const struct nd6_prproxy_soltgt *b)
{
	return (memcmp(&a->soltgt_key, &b->soltgt_key, sizeof (a->soltgt_key)));
}