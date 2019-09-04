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
struct if_llreach {int /*<<< orphan*/  lr_key; } ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static __inline int
iflr_cmp(const struct if_llreach *a, const struct if_llreach *b)
{
	return (memcmp(&a->lr_key, &b->lr_key, sizeof (a->lr_key)));
}