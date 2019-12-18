#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  TYPE_2__* mbuf_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_5__ {scalar_t__ len; } ;
struct TYPE_6__ {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  inet_cksum (TYPE_2__*,int,scalar_t__,scalar_t__) ; 

errno_t
mbuf_inet_cksum(mbuf_t mbuf, int protocol, u_int32_t offset, u_int32_t length,
    u_int16_t *csum)
{
	if (mbuf == NULL || length == 0 || csum == NULL ||
	    (u_int32_t)mbuf->m_pkthdr.len < (offset + length))
		return (EINVAL);

	*csum = inet_cksum(mbuf, protocol, offset, length);
	return (0);
}