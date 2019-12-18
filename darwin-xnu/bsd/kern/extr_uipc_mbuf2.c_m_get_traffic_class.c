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
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  mbuf_traffic_class_t ;

/* Variables and functions */
 int /*<<< orphan*/  MBUF_SC2TC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_get_service_class (struct mbuf*) ; 

mbuf_traffic_class_t
m_get_traffic_class(struct mbuf *m)
{
	return (MBUF_SC2TC(m_get_service_class(m)));
}