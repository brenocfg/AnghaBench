#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct socket {int dummy; } ;
struct secpolicy {int dummy; } ;
struct sadb_x_policy {int /*<<< orphan*/  sadb_x_policy_id; } ;
struct sadb_msghdr {int* extlen; TYPE_1__* msg; int /*<<< orphan*/ ** ext; } ;
struct mbuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sadb_msg_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOBUFS ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  KEY_SENDUP_ONE ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 size_t SADB_X_EXT_POLICY ; 
 int /*<<< orphan*/  SADB_X_SPDGET ; 
 struct secpolicy* __key_getspbyid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipseclog (int /*<<< orphan*/ ) ; 
 int key_senderror (struct socket*,struct mbuf*,int /*<<< orphan*/ ) ; 
 int key_sendup_mbuf (struct socket*,struct mbuf*,int /*<<< orphan*/ ) ; 
 struct mbuf* key_setdumpsp (struct secpolicy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  sadb_mutex ; 

__attribute__((used)) static int
key_spdget(
		   struct socket *so,
		   struct mbuf *m,
		   const struct sadb_msghdr *mhp)
{
	u_int32_t id;
	struct secpolicy *sp;
	struct mbuf *n;
	
	LCK_MTX_ASSERT(sadb_mutex, LCK_MTX_ASSERT_NOTOWNED);
	
	/* sanity check */
	if (so == NULL || m == NULL || mhp == NULL || mhp->msg == NULL)
		panic("key_spdget: NULL pointer is passed.\n");
	
	if (mhp->ext[SADB_X_EXT_POLICY] == NULL ||
	    mhp->extlen[SADB_X_EXT_POLICY] < sizeof(struct sadb_x_policy)) {
		ipseclog((LOG_DEBUG, "key_spdget: invalid message is passed.\n"));
		return key_senderror(so, m, EINVAL);
	}
	
	id = ((struct sadb_x_policy *)
		  (void *)mhp->ext[SADB_X_EXT_POLICY])->sadb_x_policy_id;
	
	/* Is there SP in SPD ? */
	lck_mtx_lock(sadb_mutex);
	if ((sp = __key_getspbyid(id)) == NULL) {
		ipseclog((LOG_DEBUG, "key_spdget: no SP found id:%u.\n", id));
		lck_mtx_unlock(sadb_mutex);
		return key_senderror(so, m, ENOENT);
	}
	lck_mtx_unlock(sadb_mutex);
	n = key_setdumpsp(sp, SADB_X_SPDGET, 0, mhp->msg->sadb_msg_pid);
	if (n != NULL) {
		m_freem(m);
		return key_sendup_mbuf(so, n, KEY_SENDUP_ONE);
	} else
		return key_senderror(so, m, ENOBUFS);
}