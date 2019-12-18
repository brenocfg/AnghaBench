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
typedef  int /*<<< orphan*/  mbuf_type_t ;
typedef  int /*<<< orphan*/ * mbuf_t ;
typedef  int /*<<< orphan*/  mbuf_how_t ;
typedef  int /*<<< orphan*/  errno_t ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * m_clattach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void (*) (int /*<<< orphan*/ *,u_int,int /*<<< orphan*/ *),size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

errno_t
mbuf_attachcluster(mbuf_how_t how, mbuf_type_t type, mbuf_t *mbuf,
    caddr_t extbuf, void (*extfree)(caddr_t, u_int, caddr_t),
    size_t extsize, caddr_t extarg)
{
	if (mbuf == NULL || extbuf == NULL || extfree == NULL || extsize == 0)
		return (EINVAL);

	if ((*mbuf = m_clattach(*mbuf, type, extbuf,
	    extfree, extsize, extarg, how, 0)) == NULL)
		return (ENOMEM);

	return (0);
}