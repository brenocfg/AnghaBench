#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  TYPE_2__* mbuf_t ;
typedef  int mbuf_csum_performed_flags_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_4__ {int csum_flags; int /*<<< orphan*/  csum_data; } ;
struct TYPE_5__ {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int mbuf_valid_csum_performed_flags ; 

errno_t
mbuf_set_csum_performed(
	mbuf_t mbuf,
	mbuf_csum_performed_flags_t performed,
	u_int32_t value)
{
	performed &= mbuf_valid_csum_performed_flags;
	mbuf->m_pkthdr.csum_flags =
	    (mbuf->m_pkthdr.csum_flags & 0xffff0000) | performed;
	mbuf->m_pkthdr.csum_data = value;

	return (0);
}