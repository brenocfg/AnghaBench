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
struct m_tag {int dummy; } ;
struct ip6aux {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERNEL_MODULE_TAG_ID ; 
 int /*<<< orphan*/  KERNEL_TAG_TYPE_INET6 ; 
 int /*<<< orphan*/  M_DONTWAIT ; 
 struct m_tag* m_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct mbuf*) ; 
 struct m_tag* m_tag_locate (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_tag_prepend (struct mbuf*,struct m_tag*) ; 

struct ip6aux *
ip6_addaux(struct mbuf *m)
{
	struct m_tag		*tag;

	/* Check if one is already allocated */
	tag = m_tag_locate(m, KERNEL_MODULE_TAG_ID,
	    KERNEL_TAG_TYPE_INET6, NULL);
	if (tag == NULL) {
		/* Allocate a tag */
		tag = m_tag_create(KERNEL_MODULE_TAG_ID, KERNEL_TAG_TYPE_INET6,
		    sizeof (struct ip6aux), M_DONTWAIT, m);

		/* Attach it to the mbuf */
		if (tag) {
			m_tag_prepend(m, tag);
		}
	}

	return (tag ? (struct ip6aux *)(tag + 1) : NULL);
}