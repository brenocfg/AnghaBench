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
typedef  scalar_t__ user_ssize_t ;
struct uio {int dummy; } ;
struct socket {int dummy; } ;
struct mbuf {struct mbuf* m_next; scalar_t__ m_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  caddr_t ; 
 int /*<<< orphan*/  m_freem_list (struct mbuf*) ; 
 int /*<<< orphan*/  mtod (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int /*<<< orphan*/ ) ; 
 int uiomove (int /*<<< orphan*/ ,int,struct uio*) ; 

__attribute__((used)) static int
sodelayed_copy(struct socket *so, struct uio *uio, struct mbuf **free_list,
    user_ssize_t *resid)
{
	int error = 0;
	struct mbuf *m;

	m = *free_list;

	socket_unlock(so, 0);

	while (m != NULL && error == 0) {
		error = uiomove(mtod(m, caddr_t), (int)m->m_len, uio);
		m = m->m_next;
	}
	m_freem_list(*free_list);

	*free_list = NULL;
	*resid = 0;

	socket_lock(so, 0);

	return (error);
}