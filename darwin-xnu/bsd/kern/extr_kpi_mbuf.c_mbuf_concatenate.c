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
typedef  int /*<<< orphan*/ * mbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  m_cat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

mbuf_t
mbuf_concatenate(mbuf_t dst, mbuf_t src)
{
	if (dst == NULL)
		return (NULL);

	m_cat(dst, src);

	/* return dst as is in the current implementation */
	return (dst);
}