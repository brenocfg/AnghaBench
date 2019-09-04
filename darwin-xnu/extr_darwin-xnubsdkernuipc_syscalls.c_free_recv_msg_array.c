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
typedef  scalar_t__ u_int ;
struct recv_msg_elem {int /*<<< orphan*/ * controlp; struct recv_msg_elem* psa; int /*<<< orphan*/ * uio; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  _FREE (struct recv_msg_elem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uio_free (int /*<<< orphan*/ *) ; 

void
free_recv_msg_array(struct recv_msg_elem *recv_msg_array, u_int count)
{
	u_int i;

	for (i = 0; i < count; i++) {
		struct recv_msg_elem *recv_msg_elem = recv_msg_array + i;

		if (recv_msg_elem->uio != NULL)
			uio_free(recv_msg_elem->uio);
		if (recv_msg_elem->psa != NULL)
			_FREE(recv_msg_elem->psa, M_TEMP);
		if (recv_msg_elem->controlp != NULL)
			m_freem(recv_msg_elem->controlp);
	}
	_FREE(recv_msg_array, M_TEMP);
}