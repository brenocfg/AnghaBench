#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_data_ready; } ;
struct sctp_shared_key {int /*<<< orphan*/  key_list; } ;
struct TYPE_3__ {void* length; int /*<<< orphan*/  type; } ;
struct sctp_hmac_algo_param {TYPE_1__ param_hdr; int /*<<< orphan*/ * chunks; void** hmac_ids; } ;
struct TYPE_4__ {int malloced; struct sock* sk; int /*<<< orphan*/  bind_addr; int /*<<< orphan*/  inqueue; scalar_t__ dead; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  type; } ;
struct sctp_endpoint {struct sctp_hmac_algo_param* digest; int /*<<< orphan*/  endpoint_shared_keys; struct sctp_hmac_algo_param* auth_chunk_list; struct sctp_hmac_algo_param* auth_hmacs_list; int /*<<< orphan*/  key_changed_at; scalar_t__ current_key; scalar_t__ last_key; int /*<<< orphan*/ * secret_key; int /*<<< orphan*/  rcvbuf_policy; int /*<<< orphan*/  sndbuf_policy; int /*<<< orphan*/  asocs; TYPE_2__ base; } ;
struct sctp_chunks_param {TYPE_1__ param_hdr; int /*<<< orphan*/ * chunks; void** hmac_ids; } ;
typedef  int /*<<< orphan*/  sctp_paramhdr_t ;
typedef  int /*<<< orphan*/  sctp_hmac_algo_param_t ;
typedef  int /*<<< orphan*/  sctp_chunks_param_t ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int SCTP_AUTH_HMAC_ID_SHA1 ; 
 int SCTP_AUTH_NUM_HMACS ; 
 int /*<<< orphan*/  SCTP_CID_ASCONF ; 
 int /*<<< orphan*/  SCTP_CID_ASCONF_ACK ; 
 int /*<<< orphan*/  SCTP_EP_TYPE_SOCKET ; 
 int SCTP_NUM_CHUNK_TYPES ; 
 int /*<<< orphan*/  SCTP_PARAM_CHUNKS ; 
 int /*<<< orphan*/  SCTP_PARAM_HMAC_ALGO ; 
 int /*<<< orphan*/  SCTP_SECRET_SIZE ; 
 int SCTP_SIGNATURE_SIZE ; 
 int /*<<< orphan*/  SOCK_USE_WRITE_QUEUE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* htons (int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (struct sctp_hmac_algo_param*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sctp_addip_enable ; 
 int /*<<< orphan*/  sctp_auth_destroy_keys (int /*<<< orphan*/ *) ; 
 scalar_t__ sctp_auth_enable ; 
 int sctp_auth_init_hmacs (struct sctp_endpoint*,int /*<<< orphan*/ ) ; 
 struct sctp_shared_key* sctp_auth_shkey_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_bind_addr_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_data_ready ; 
 int /*<<< orphan*/  sctp_endpoint_bh_rcv ; 
 int /*<<< orphan*/  sctp_inq_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_inq_set_th_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_rcvbuf_policy ; 
 int /*<<< orphan*/  sctp_sndbuf_policy ; 
 int /*<<< orphan*/  sctp_write_space ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sctp_endpoint *sctp_endpoint_init(struct sctp_endpoint *ep,
						struct sock *sk,
						gfp_t gfp)
{
	struct sctp_hmac_algo_param *auth_hmacs = NULL;
	struct sctp_chunks_param *auth_chunks = NULL;
	struct sctp_shared_key *null_key;
	int err;

	ep->digest = kzalloc(SCTP_SIGNATURE_SIZE, gfp);
	if (!ep->digest)
		return NULL;

	if (sctp_auth_enable) {
		/* Allocate space for HMACS and CHUNKS authentication
		 * variables.  There are arrays that we encode directly
		 * into parameters to make the rest of the operations easier.
		 */
		auth_hmacs = kzalloc(sizeof(sctp_hmac_algo_param_t) +
				sizeof(__u16) * SCTP_AUTH_NUM_HMACS, gfp);
		if (!auth_hmacs)
			goto nomem;

		auth_chunks = kzalloc(sizeof(sctp_chunks_param_t) +
					SCTP_NUM_CHUNK_TYPES, gfp);
		if (!auth_chunks)
			goto nomem;

		/* Initialize the HMACS parameter.
		 * SCTP-AUTH: Section 3.3
		 *    Every endpoint supporting SCTP chunk authentication MUST
		 *    support the HMAC based on the SHA-1 algorithm.
		 */
		auth_hmacs->param_hdr.type = SCTP_PARAM_HMAC_ALGO;
		auth_hmacs->param_hdr.length =
					htons(sizeof(sctp_paramhdr_t) + 2);
		auth_hmacs->hmac_ids[0] = htons(SCTP_AUTH_HMAC_ID_SHA1);

		/* Initialize the CHUNKS parameter */
		auth_chunks->param_hdr.type = SCTP_PARAM_CHUNKS;
		auth_chunks->param_hdr.length = htons(sizeof(sctp_paramhdr_t));

		/* If the Add-IP functionality is enabled, we must
		 * authenticate, ASCONF and ASCONF-ACK chunks
		 */
		if (sctp_addip_enable) {
			auth_chunks->chunks[0] = SCTP_CID_ASCONF;
			auth_chunks->chunks[1] = SCTP_CID_ASCONF_ACK;
			auth_chunks->param_hdr.length =
					htons(sizeof(sctp_paramhdr_t) + 2);
		}
	}

	/* Initialize the base structure. */
	/* What type of endpoint are we?  */
	ep->base.type = SCTP_EP_TYPE_SOCKET;

	/* Initialize the basic object fields. */
	atomic_set(&ep->base.refcnt, 1);
	ep->base.dead = 0;
	ep->base.malloced = 1;

	/* Create an input queue.  */
	sctp_inq_init(&ep->base.inqueue);

	/* Set its top-half handler */
	sctp_inq_set_th_handler(&ep->base.inqueue, sctp_endpoint_bh_rcv);

	/* Initialize the bind addr area */
	sctp_bind_addr_init(&ep->base.bind_addr, 0);

	/* Remember who we are attached to.  */
	ep->base.sk = sk;
	sock_hold(ep->base.sk);

	/* Create the lists of associations.  */
	INIT_LIST_HEAD(&ep->asocs);

	/* Use SCTP specific send buffer space queues.  */
	ep->sndbuf_policy = sctp_sndbuf_policy;

	sk->sk_data_ready = sctp_data_ready;
	sk->sk_write_space = sctp_write_space;
	sock_set_flag(sk, SOCK_USE_WRITE_QUEUE);

	/* Get the receive buffer policy for this endpoint */
	ep->rcvbuf_policy = sctp_rcvbuf_policy;

	/* Initialize the secret key used with cookie. */
	get_random_bytes(&ep->secret_key[0], SCTP_SECRET_SIZE);
	ep->last_key = ep->current_key = 0;
	ep->key_changed_at = jiffies;

	/* SCTP-AUTH extensions*/
	INIT_LIST_HEAD(&ep->endpoint_shared_keys);
	null_key = sctp_auth_shkey_create(0, GFP_KERNEL);
	if (!null_key)
		goto nomem;

	list_add(&null_key->key_list, &ep->endpoint_shared_keys);

	/* Allocate and initialize transorms arrays for suported HMACs. */
	err = sctp_auth_init_hmacs(ep, gfp);
	if (err)
		goto nomem_hmacs;

	/* Add the null key to the endpoint shared keys list and
	 * set the hmcas and chunks pointers.
	 */
	ep->auth_hmacs_list = auth_hmacs;
	ep->auth_chunk_list = auth_chunks;

	return ep;

nomem_hmacs:
	sctp_auth_destroy_keys(&ep->endpoint_shared_keys);
nomem:
	/* Free all allocations */
	kfree(auth_hmacs);
	kfree(auth_chunks);
	kfree(ep->digest);
	return NULL;

}