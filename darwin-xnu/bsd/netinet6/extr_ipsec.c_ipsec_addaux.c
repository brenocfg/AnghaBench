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
struct ipsec_tag {scalar_t__ history_count; scalar_t__ socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPSEC_TAG_SIZE ; 
 int /*<<< orphan*/  KERNEL_MODULE_TAG_ID ; 
 int /*<<< orphan*/  KERNEL_TAG_TYPE_IPSEC ; 
 int /*<<< orphan*/  M_DONTWAIT ; 
 struct m_tag* m_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*) ; 
 struct m_tag* m_tag_locate (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_tag_prepend (struct mbuf*,struct m_tag*) ; 

__attribute__((used)) static struct ipsec_tag *
ipsec_addaux(
	struct mbuf *m)
{
	struct m_tag		*tag;
	
	/* Check if the tag already exists */
	tag = m_tag_locate(m, KERNEL_MODULE_TAG_ID, KERNEL_TAG_TYPE_IPSEC, NULL);
	
	if (tag == NULL) {
		struct ipsec_tag	*itag;
		
		/* Allocate a tag */
		tag = m_tag_create(KERNEL_MODULE_TAG_ID, KERNEL_TAG_TYPE_IPSEC,
						  IPSEC_TAG_SIZE, M_DONTWAIT, m);
		
		if (tag) {
			itag = (struct ipsec_tag*)(tag + 1);
			itag->socket = 0;
			itag->history_count = 0;
			
			m_tag_prepend(m, tag);
		}
	}
	
	return tag ? (struct ipsec_tag*)(tag + 1) : NULL;
}