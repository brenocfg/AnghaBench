#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_int32_t ;
struct m_tag {int dummy; } ;
struct m_drvaux_tag {size_t da_length; void* da_subfamily; void* da_family; } ;
typedef  TYPE_1__* mbuf_t ;
typedef  int /*<<< orphan*/  mbuf_how_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_6__ {int m_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EWOULDBLOCK ; 
 int /*<<< orphan*/  KERNEL_MODULE_TAG_ID ; 
 int /*<<< orphan*/  KERNEL_TAG_TYPE_DRVAUX ; 
 size_t MBUF_DRVAUX_MAXLEN ; 
 int /*<<< orphan*/  MBUF_WAITOK ; 
 int M_PKTHDR ; 
 struct m_tag* m_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct m_tag* m_tag_locate (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_tag_prepend (TYPE_1__*,struct m_tag*) ; 

errno_t
mbuf_add_drvaux(mbuf_t mbuf, mbuf_how_t how, u_int32_t family,
    u_int32_t subfamily, size_t length, void **data_p)
{
	struct m_drvaux_tag *p;
	struct m_tag *tag;

	if (mbuf == NULL || !(mbuf->m_flags & M_PKTHDR) ||
	    length == 0 || length > MBUF_DRVAUX_MAXLEN)
		return (EINVAL);

	if (data_p != NULL)
		*data_p = NULL;

	/* Check if one is already associated */
	if ((tag = m_tag_locate(mbuf, KERNEL_MODULE_TAG_ID,
	    KERNEL_TAG_TYPE_DRVAUX, NULL)) != NULL)
		return (EEXIST);

	/* Tag is (m_drvaux_tag + module specific data) */
	if ((tag = m_tag_create(KERNEL_MODULE_TAG_ID, KERNEL_TAG_TYPE_DRVAUX,
	    sizeof (*p) + length, how, mbuf)) == NULL)
		return ((how == MBUF_WAITOK) ? ENOMEM : EWOULDBLOCK);

	p = (struct m_drvaux_tag *)(tag + 1);
	p->da_family = family;
	p->da_subfamily = subfamily;
	p->da_length = length;

	/* Associate the tag */
	m_tag_prepend(mbuf, tag);

	if (data_p != NULL)
		*data_p = (p + 1);

	return (0);
}