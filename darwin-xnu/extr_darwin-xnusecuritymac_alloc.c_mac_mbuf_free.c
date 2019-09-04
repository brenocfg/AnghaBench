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

/* Variables and functions */

void
mac_mbuf_free(void *data)
{
#if CONFIG_MACF_SOCKET_SUBSET
	struct m_tag *t;

	t = (struct m_tag *)((char *)data - sizeof(struct m_tag));
	m_tag_free(t);
#else
#pragma unused(data)
#endif
}