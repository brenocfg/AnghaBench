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
typedef  scalar_t__ u_int32_t ;
typedef  scalar_t__ mbuf_traffic_class_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ MBUF_SCIDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBUF_TC2SCVAL (scalar_t__) ; 
 scalar_t__ MBUF_TC_MAX ; 
 int /*<<< orphan*/  m_service_class_from_val (int /*<<< orphan*/ ) ; 

errno_t
mbuf_get_traffic_class_index(mbuf_traffic_class_t tc, u_int32_t *index)
{
	if (index == NULL || (u_int32_t)tc >= MBUF_TC_MAX)
		return (EINVAL);

	*index = MBUF_SCIDX(m_service_class_from_val(MBUF_TC2SCVAL(tc)));
	return (0);
}