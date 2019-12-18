#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct m_tag {int dummy; } ;
typedef  int /*<<< orphan*/  mbuf_tag_type_t ;
typedef  scalar_t__ mbuf_tag_id_t ;
typedef  TYPE_1__* mbuf_t ;
struct TYPE_5__ {int m_flags; } ;

/* Variables and functions */
 int M_PKTHDR ; 
 int /*<<< orphan*/  NSI_MBUF_TAG ; 
 int /*<<< orphan*/  m_tag_delete (TYPE_1__*,struct m_tag*) ; 
 struct m_tag* m_tag_locate (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_str_id_first_last (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 

void
mbuf_tag_free(
	mbuf_t			mbuf,
	mbuf_tag_id_t	id,
	mbuf_tag_type_t	type)
{
	struct m_tag *tag;
	u_int32_t mtag_id_first, mtag_id_last;

	/* Sanity check parameters */
	(void) net_str_id_first_last(&mtag_id_first, &mtag_id_last,
	    NSI_MBUF_TAG);
	if (mbuf == NULL || (mbuf->m_flags & M_PKTHDR) == 0 ||
	    id < mtag_id_first || id > mtag_id_last)
		return;

	tag = m_tag_locate(mbuf, id, type, NULL);
	if (tag == NULL) {
		return;
	}

	m_tag_delete(mbuf, tag);
}