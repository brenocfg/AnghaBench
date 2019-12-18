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
typedef  int /*<<< orphan*/  u_int32_t ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  mbuf_traffic_class_t ;

/* Variables and functions */
 int /*<<< orphan*/  MBUF_TC2SCVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_service_class_from_val (int /*<<< orphan*/ ) ; 
 int m_set_service_class (struct mbuf*,int /*<<< orphan*/ ) ; 

int
m_set_traffic_class(struct mbuf *m, mbuf_traffic_class_t tc)
{
	u_int32_t val = MBUF_TC2SCVAL(tc);	/* just the val portion */

	return (m_set_service_class(m, m_service_class_from_val(val)));
}