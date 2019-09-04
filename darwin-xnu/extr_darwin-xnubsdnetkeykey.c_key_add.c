#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  scalar_t__ u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct socket {int dummy; } ;
struct secasvar {int flags; } ;
struct secasindex {int dummy; } ;
struct TYPE_8__ {scalar_t__ ss_family; } ;
struct TYPE_9__ {scalar_t__ mode; TYPE_2__ dst; } ;
struct secashead {TYPE_3__ saidx; } ;
struct sadb_x_sa2 {scalar_t__ sadb_x_sa2_reqid; int /*<<< orphan*/  sadb_x_sa2_mode; } ;
struct sadb_sa {int /*<<< orphan*/  sadb_sa_spi; } ;
struct sadb_msghdr {int* extlen; int /*<<< orphan*/ ** ext; TYPE_1__* msg; } ;
struct sadb_address {int dummy; } ;
struct mbuf {int dummy; } ;
typedef  TYPE_4__* ifnet_t ;
struct TYPE_10__ {int /*<<< orphan*/  if_index; } ;
struct TYPE_7__ {scalar_t__ sadb_msg_satype; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  IPSEC_DIR_OUTBOUND ; 
 int /*<<< orphan*/  IPSEC_MODE_ANY ; 
 scalar_t__ IPSEC_MODE_TRANSPORT ; 
 int /*<<< orphan*/  KEY_SADB_LOCKED ; 
 int /*<<< orphan*/  KEY_SENDUP_ALL ; 
 int /*<<< orphan*/  KEY_SETSECASIDX (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct sadb_address*,struct sadb_address*,int /*<<< orphan*/ ,struct secasindex*) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 size_t SADB_EXT_ADDRESS_DST ; 
 size_t SADB_EXT_ADDRESS_SRC ; 
 size_t SADB_EXT_KEY_AUTH ; 
 size_t SADB_EXT_KEY_ENCRYPT ; 
 size_t SADB_EXT_LIFETIME_HARD ; 
 size_t SADB_EXT_LIFETIME_SOFT ; 
 size_t SADB_EXT_SA ; 
 scalar_t__ SADB_SATYPE_AH ; 
 scalar_t__ SADB_SATYPE_ESP ; 
 int /*<<< orphan*/  SADB_X_EXT_IPSECIF ; 
 int SADB_X_EXT_NATT_MULTIPLEUSERS ; 
 size_t SADB_X_EXT_SA2 ; 
 int /*<<< orphan*/  bzero_keys (struct sadb_msghdr const*) ; 
 int /*<<< orphan*/  ipseclog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_freesav (struct secasvar*,int /*<<< orphan*/ ) ; 
 TYPE_4__* key_get_ipsec_if_from_message (struct sadb_msghdr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_get_outgoing_ifindex_from_message (struct sadb_msghdr const*,int /*<<< orphan*/ ) ; 
 struct mbuf* key_getmsgbuf_x1 (struct mbuf*,struct sadb_msghdr const*) ; 
 struct secashead* key_getsah (struct secasindex*) ; 
 scalar_t__ key_getsavbyspi (struct secashead*,int /*<<< orphan*/ ) ; 
 int key_mature (struct secasvar*) ; 
 struct secashead* key_newsah (struct secasindex*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct secasvar* key_newsav (struct mbuf*,struct sadb_msghdr const*,struct secashead*,int*,struct socket*) ; 
 int /*<<< orphan*/  key_satype2proto (scalar_t__) ; 
 int key_senderror (struct socket*,struct mbuf*,int) ; 
 int key_sendup_mbuf (struct socket*,struct mbuf*,int /*<<< orphan*/ ) ; 
 int key_setident (struct secashead*,struct mbuf*,struct sadb_msghdr const*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  sadb_mutex ; 

__attribute__((used)) static int
key_add(
		struct socket *so,
		struct mbuf *m,
		const struct sadb_msghdr *mhp)
{
	struct sadb_sa *sa0;
	struct sadb_address *src0, *dst0;
	ifnet_t ipsec_if = NULL;
	struct secasindex saidx;
	struct secashead *newsah;
	struct secasvar *newsav;
	u_int16_t proto;
	u_int8_t mode;
	u_int32_t reqid;
	int error;
	
	LCK_MTX_ASSERT(sadb_mutex, LCK_MTX_ASSERT_NOTOWNED);
	
	/* sanity check */
	if (so == NULL || m == NULL || mhp == NULL || mhp->msg == NULL)
		panic("key_add: NULL pointer is passed.\n");
	
	/* map satype to proto */
	if ((proto = key_satype2proto(mhp->msg->sadb_msg_satype)) == 0) {
		ipseclog((LOG_DEBUG, "key_add: invalid satype is passed.\n"));
		bzero_keys(mhp);
		return key_senderror(so, m, EINVAL);
	}
	
	if (mhp->ext[SADB_EXT_SA] == NULL ||
	    mhp->ext[SADB_EXT_ADDRESS_SRC] == NULL ||
	    mhp->ext[SADB_EXT_ADDRESS_DST] == NULL ||
	    (mhp->msg->sadb_msg_satype == SADB_SATYPE_ESP &&
	     mhp->ext[SADB_EXT_KEY_ENCRYPT] == NULL) ||
	    (mhp->msg->sadb_msg_satype == SADB_SATYPE_AH &&
	     mhp->ext[SADB_EXT_KEY_AUTH] == NULL) ||
	    (mhp->ext[SADB_EXT_LIFETIME_HARD] != NULL &&
	     mhp->ext[SADB_EXT_LIFETIME_SOFT] == NULL) ||
	    (mhp->ext[SADB_EXT_LIFETIME_HARD] == NULL &&
	     mhp->ext[SADB_EXT_LIFETIME_SOFT] != NULL)) {
			ipseclog((LOG_DEBUG, "key_add: invalid message is passed.\n"));
			bzero_keys(mhp);
			return key_senderror(so, m, EINVAL);
		}
	if (mhp->extlen[SADB_EXT_SA] < sizeof(struct sadb_sa) ||
	    mhp->extlen[SADB_EXT_ADDRESS_SRC] < sizeof(struct sadb_address) ||
	    mhp->extlen[SADB_EXT_ADDRESS_DST] < sizeof(struct sadb_address)) {
		/* XXX need more */
		ipseclog((LOG_DEBUG, "key_add: invalid message is passed.\n"));
		bzero_keys(mhp);
		return key_senderror(so, m, EINVAL);
	}
	if (mhp->ext[SADB_X_EXT_SA2] != NULL) {
		mode = ((struct sadb_x_sa2 *)
				(void *)mhp->ext[SADB_X_EXT_SA2])->sadb_x_sa2_mode;
		reqid = ((struct sadb_x_sa2 *)
				 (void *)mhp->ext[SADB_X_EXT_SA2])->sadb_x_sa2_reqid;
	} else {
		mode = IPSEC_MODE_ANY;
		reqid = 0;
	}
	
	sa0 = (struct sadb_sa *)(void *)mhp->ext[SADB_EXT_SA];
	src0 = (struct sadb_address *)mhp->ext[SADB_EXT_ADDRESS_SRC];
	dst0 = (struct sadb_address *)mhp->ext[SADB_EXT_ADDRESS_DST];
	ipsec_if = key_get_ipsec_if_from_message(mhp, SADB_X_EXT_IPSECIF);
	
	/* XXX boundary check against sa_len */
	KEY_SETSECASIDX(proto, mode, reqid, src0 + 1, dst0 + 1, ipsec_if ? ipsec_if->if_index : 0, &saidx);
	
	lck_mtx_lock(sadb_mutex);
	
	/* get a SA header */
	if ((newsah = key_getsah(&saidx)) == NULL) {
		/* create a new SA header: key_addspi is always used for outbound spi */
		if ((newsah = key_newsah(&saidx, ipsec_if, key_get_outgoing_ifindex_from_message(mhp, SADB_X_EXT_IPSECIF), IPSEC_DIR_OUTBOUND)) == NULL) {
			lck_mtx_unlock(sadb_mutex);
			ipseclog((LOG_DEBUG, "key_add: No more memory.\n"));
			bzero_keys(mhp);
			return key_senderror(so, m, ENOBUFS);
		}
	}
	
	/* set spidx if there */
	/* XXX rewrite */
	error = key_setident(newsah, m, mhp);
	if (error) {
		lck_mtx_unlock(sadb_mutex);
		bzero_keys(mhp);
		return key_senderror(so, m, error);
	}
	
	/* create new SA entry. */
	/* We can create new SA only if SPI is different. */
	if (key_getsavbyspi(newsah, sa0->sadb_sa_spi)) {
		lck_mtx_unlock(sadb_mutex);
		ipseclog((LOG_DEBUG, "key_add: SA already exists.\n"));
		bzero_keys(mhp);
		return key_senderror(so, m, EEXIST);
	}
	newsav = key_newsav(m, mhp, newsah, &error, so);
	if (newsav == NULL) {
		lck_mtx_unlock(sadb_mutex);
		bzero_keys(mhp);
		return key_senderror(so, m, error);
	}
	
	/*
	 * Verify if SADB_X_EXT_NATT_MULTIPLEUSERS flag is set that
	 * this SA is for transport mode - otherwise clear it.
	 */
	if ((newsav->flags & SADB_X_EXT_NATT_MULTIPLEUSERS) != 0 &&
		(newsah->saidx.mode != IPSEC_MODE_TRANSPORT ||
		 newsah->saidx.dst.ss_family != AF_INET))
		newsav->flags &= ~SADB_X_EXT_NATT_MULTIPLEUSERS;
	
	/* check SA values to be mature. */
	if ((error = key_mature(newsav)) != 0) {
		key_freesav(newsav, KEY_SADB_LOCKED);
		lck_mtx_unlock(sadb_mutex);
		bzero_keys(mhp);
		return key_senderror(so, m, error);
	}
	
	lck_mtx_unlock(sadb_mutex);
	
	/*
	 * don't call key_freesav() here, as we would like to keep the SA
	 * in the database on success.
	 */
	
    {
		struct mbuf *n;
		
		/* set msg buf from mhp */
		n = key_getmsgbuf_x1(m, mhp);
		if (n == NULL) {
			ipseclog((LOG_DEBUG, "key_update: No more memory.\n"));
			bzero_keys(mhp);
			return key_senderror(so, m, ENOBUFS);
		}
		
		// mh.ext points to the mbuf content.
		// Zero out Encryption and Integrity keys if present.
		bzero_keys(mhp);
		m_freem(m);
		return key_sendup_mbuf(so, n, KEY_SENDUP_ALL);
    }
}