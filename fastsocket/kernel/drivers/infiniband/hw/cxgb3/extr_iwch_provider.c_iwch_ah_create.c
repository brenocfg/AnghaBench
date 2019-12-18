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
struct ib_pd {int dummy; } ;
struct ib_ah_attr {int dummy; } ;
struct ib_ah {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 struct ib_ah* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ib_ah *iwch_ah_create(struct ib_pd *pd,
				    struct ib_ah_attr *ah_attr)
{
	return ERR_PTR(-ENOSYS);
}