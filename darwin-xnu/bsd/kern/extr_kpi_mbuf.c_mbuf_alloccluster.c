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
typedef  int /*<<< orphan*/  mbuf_how_t ;
typedef  int /*<<< orphan*/  errno_t ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOTSUP ; 
 size_t M16KCLBYTES ; 
 size_t MBIGCLBYTES ; 
 size_t MCLBYTES ; 
 int /*<<< orphan*/ * m_16kalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * m_bigalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * m_mclalloc (int /*<<< orphan*/ ) ; 
 scalar_t__ njcl ; 

errno_t
mbuf_alloccluster(mbuf_how_t how, size_t *size, caddr_t *addr)
{
	if (size == NULL || *size == 0 || addr == NULL)
		return (EINVAL);

	*addr = NULL;

	/* Jumbo cluster pool not available? */
	if (*size > MBIGCLBYTES && njcl == 0)
		return (ENOTSUP);

	if (*size <= MCLBYTES && (*addr = m_mclalloc(how)) != NULL)
		*size = MCLBYTES;
	else if (*size > MCLBYTES && *size <= MBIGCLBYTES &&
	    (*addr = m_bigalloc(how)) != NULL)
		*size = MBIGCLBYTES;
	else if (*size > MBIGCLBYTES && *size <= M16KCLBYTES &&
	    (*addr = m_16kalloc(how)) != NULL)
		*size = M16KCLBYTES;
	else
		*size = 0;

	if (*addr == NULL)
		return (ENOMEM);

	return (0);
}