#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  TYPE_1__* mbuf_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_4__ {int m_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int M_EXT ; 
 int /*<<< orphan*/  m_ext_get_prop (TYPE_1__*) ; 

errno_t
mbuf_cluster_get_prop(mbuf_t mbuf, u_int32_t *prop)
{
	if (mbuf == NULL || prop == NULL || !(mbuf->m_flags & M_EXT))
		return (EINVAL);

	*prop = m_ext_get_prop(mbuf);
	return (0);
}