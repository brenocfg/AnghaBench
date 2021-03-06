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
struct qib_devdata {int dummy; } ;

/* Variables and functions */
 struct qib_devdata* idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qib_unit_table ; 

__attribute__((used)) static inline struct qib_devdata *__qib_lookup(int unit)
{
	return idr_find(&qib_unit_table, unit);
}