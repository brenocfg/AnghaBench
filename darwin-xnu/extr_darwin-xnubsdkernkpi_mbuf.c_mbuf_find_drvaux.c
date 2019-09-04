#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct m_tag {int m_tag_len; } ;
struct m_drvaux_tag {scalar_t__ da_length; scalar_t__ da_family; scalar_t__ da_subfamily; } ;
typedef  TYPE_1__* mbuf_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_4__ {int m_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  KERNEL_MODULE_TAG_ID ; 
 int /*<<< orphan*/  KERNEL_TAG_TYPE_DRVAUX ; 
 scalar_t__ MBUF_DRVAUX_MAXLEN ; 
 int M_PKTHDR ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 struct m_tag* m_tag_locate (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

errno_t
mbuf_find_drvaux(mbuf_t mbuf, u_int32_t *family_p, u_int32_t *subfamily_p,
    u_int32_t *length_p, void **data_p)
{
	struct m_drvaux_tag *p;
	struct m_tag *tag;

	if (mbuf == NULL || !(mbuf->m_flags & M_PKTHDR) || data_p == NULL)
		return (EINVAL);

	*data_p = NULL;

	if ((tag = m_tag_locate(mbuf, KERNEL_MODULE_TAG_ID,
	    KERNEL_TAG_TYPE_DRVAUX, NULL)) == NULL)
		return (ENOENT);

	/* Must be at least size of m_drvaux_tag */
	VERIFY(tag->m_tag_len >= sizeof (*p));

	p = (struct m_drvaux_tag *)(tag + 1);
	VERIFY(p->da_length > 0 && p->da_length <= MBUF_DRVAUX_MAXLEN);

	if (family_p != NULL)
		*family_p = p->da_family;
	if (subfamily_p != NULL)
		*subfamily_p = p->da_subfamily;
	if (length_p != NULL)
		*length_p = p->da_length;

	*data_p = (p + 1);

	return (0);
}