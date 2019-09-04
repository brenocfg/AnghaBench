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
typedef  int /*<<< orphan*/  mbuf_svc_class_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  MBUF_SCIDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBUF_VALID_SC (int /*<<< orphan*/ ) ; 

errno_t
mbuf_get_service_class_index(mbuf_svc_class_t sc, u_int32_t *index)
{
	if (index == NULL || !MBUF_VALID_SC(sc))
		return (EINVAL);

	*index = MBUF_SCIDX(sc);
	return (0);
}