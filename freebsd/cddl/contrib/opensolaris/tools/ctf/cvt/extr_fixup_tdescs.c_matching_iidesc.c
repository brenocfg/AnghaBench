#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct match {int /*<<< orphan*/  m_ret; int /*<<< orphan*/  m_name; } ;
struct TYPE_2__ {scalar_t__ ii_type; int /*<<< orphan*/  ii_dtype; int /*<<< orphan*/  ii_name; } ;
typedef  TYPE_1__ iidesc_t ;

/* Variables and functions */
 scalar_t__ II_SOU ; 
 scalar_t__ II_TYPE ; 
 int /*<<< orphan*/  streq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
matching_iidesc(void *arg1, void *arg2)
{
	iidesc_t *iidesc = arg1;
	struct match *match = arg2;
	if (!streq(iidesc->ii_name, match->m_name))
		return (0);

	if (iidesc->ii_type != II_TYPE && iidesc->ii_type != II_SOU)
		return (0);

	match->m_ret = iidesc->ii_dtype;
	return (-1);
}