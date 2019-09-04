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
typedef  scalar_t__ mbuf_type_t ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ MBUF_TYPE_FREE ; 
 int /*<<< orphan*/  m_mchtype (int /*<<< orphan*/ ,scalar_t__) ; 

errno_t
mbuf_settype(mbuf_t mbuf, mbuf_type_t new_type)
{
	if (new_type == MBUF_TYPE_FREE)
		return (EINVAL);

	m_mchtype(mbuf, new_type);

	return (0);
}