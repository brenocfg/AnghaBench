#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rxrpc_key_token {TYPE_2__* kad; int /*<<< orphan*/  security_index; } ;
struct rxrpc_connection {int security_level; int size_align; int security_size; int header_size; struct crypto_blkcipher* cipher; int /*<<< orphan*/  security_ix; TYPE_3__* key; int /*<<< orphan*/  debug_id; } ;
struct rxkad_level2_hdr {int dummy; } ;
struct rxkad_level1_hdr {int dummy; } ;
struct crypto_blkcipher {int dummy; } ;
struct TYPE_4__ {struct rxrpc_key_token* data; } ;
struct TYPE_6__ {TYPE_1__ payload; } ;
struct TYPE_5__ {int /*<<< orphan*/  session_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 int EKEYREJECTED ; 
 scalar_t__ IS_ERR (struct crypto_blkcipher*) ; 
 int PTR_ERR (struct crypto_blkcipher*) ; 
#define  RXRPC_SECURITY_AUTH 130 
#define  RXRPC_SECURITY_ENCRYPT 129 
#define  RXRPC_SECURITY_PLAIN 128 
 int /*<<< orphan*/  _debug (char*) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 struct crypto_blkcipher* crypto_alloc_blkcipher (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_blkcipher_setkey (struct crypto_blkcipher*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  key_serial (TYPE_3__*) ; 

__attribute__((used)) static int rxkad_init_connection_security(struct rxrpc_connection *conn)
{
	struct crypto_blkcipher *ci;
	struct rxrpc_key_token *token;
	int ret;

	_enter("{%d},{%x}", conn->debug_id, key_serial(conn->key));

	token = conn->key->payload.data;
	conn->security_ix = token->security_index;

	ci = crypto_alloc_blkcipher("pcbc(fcrypt)", 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(ci)) {
		_debug("no cipher");
		ret = PTR_ERR(ci);
		goto error;
	}

	if (crypto_blkcipher_setkey(ci, token->kad->session_key,
				    sizeof(token->kad->session_key)) < 0)
		BUG();

	switch (conn->security_level) {
	case RXRPC_SECURITY_PLAIN:
		break;
	case RXRPC_SECURITY_AUTH:
		conn->size_align = 8;
		conn->security_size = sizeof(struct rxkad_level1_hdr);
		conn->header_size += sizeof(struct rxkad_level1_hdr);
		break;
	case RXRPC_SECURITY_ENCRYPT:
		conn->size_align = 8;
		conn->security_size = sizeof(struct rxkad_level2_hdr);
		conn->header_size += sizeof(struct rxkad_level2_hdr);
		break;
	default:
		ret = -EKEYREJECTED;
		goto error;
	}

	conn->cipher = ci;
	ret = 0;
error:
	_leave(" = %d", ret);
	return ret;
}