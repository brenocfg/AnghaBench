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
struct scatterlist {int dummy; } ;
struct rxrpc_crypt {int /*<<< orphan*/  x; int /*<<< orphan*/ * n; } ;
struct rxrpc_connection {int dummy; } ;
struct rxkad_response {int /*<<< orphan*/  encrypted; } ;
struct blkcipher_desc {scalar_t__ flags; int /*<<< orphan*/  info; int /*<<< orphan*/ * tfm; } ;
typedef  int /*<<< orphan*/  iv ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  crypto_blkcipher_decrypt_iv (struct blkcipher_desc*,struct scatterlist*,struct scatterlist*,int) ; 
 scalar_t__ crypto_blkcipher_setkey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct rxrpc_crypt*,struct rxrpc_crypt const*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rxkad_ci ; 
 int /*<<< orphan*/  rxkad_ci_mutex ; 
 int /*<<< orphan*/  rxkad_sg_set_buf2 (struct scatterlist*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void rxkad_decrypt_response(struct rxrpc_connection *conn,
				   struct rxkad_response *resp,
				   const struct rxrpc_crypt *session_key)
{
	struct blkcipher_desc desc;
	struct scatterlist sg[2];
	struct rxrpc_crypt iv;

	_enter(",,%08x%08x",
	       ntohl(session_key->n[0]), ntohl(session_key->n[1]));

	ASSERT(rxkad_ci != NULL);

	mutex_lock(&rxkad_ci_mutex);
	if (crypto_blkcipher_setkey(rxkad_ci, session_key->x,
				    sizeof(*session_key)) < 0)
		BUG();

	memcpy(&iv, session_key, sizeof(iv));
	desc.tfm = rxkad_ci;
	desc.info = iv.x;
	desc.flags = 0;

	rxkad_sg_set_buf2(sg, &resp->encrypted, sizeof(resp->encrypted));
	crypto_blkcipher_decrypt_iv(&desc, sg, sg, sizeof(resp->encrypted));
	mutex_unlock(&rxkad_ci_mutex);

	_leave("");
}