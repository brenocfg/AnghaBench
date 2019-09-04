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
typedef  int /*<<< orphan*/  thread_qos_t ;
struct uu_workq_policy {int /*<<< orphan*/  qos_bucket; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workq_pri_bucket (struct uu_workq_policy) ; 

__attribute__((used)) static inline thread_qos_t
workq_pri_override(struct uu_workq_policy req)
{
	return MAX(workq_pri_bucket(req), req.qos_bucket);
}