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
struct m_tag {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERNEL_MODULE_TAG_ID ; 
 int /*<<< orphan*/  KERNEL_TAG_TYPE_MAC_POLICY_LABEL ; 
 struct m_tag* m_tag_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void *
mac_mbuf_alloc(int len, int wait)
{
#if CONFIG_MACF_SOCKET_SUBSET
	struct m_tag *t;

	t = m_tag_alloc(KERNEL_MODULE_TAG_ID, KERNEL_TAG_TYPE_MAC_POLICY_LABEL,
			len, wait);
	if (t == NULL)
		return (NULL);

	return ((void *)(t + 1));
#else
#pragma unused(len, wait)
	return NULL;
#endif
}