#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  serial; } ;
struct rxrpc_skb_priv {TYPE_4__ hdr; } ;
struct rxrpc_key_token {TYPE_5__* kad; } ;
struct rxrpc_connection {scalar_t__ security_level; scalar_t__ security_ix; TYPE_2__** channels; int /*<<< orphan*/  cid; int /*<<< orphan*/  epoch; TYPE_7__* key; int /*<<< orphan*/  debug_id; } ;
struct TYPE_11__ {void* level; void* inc_nonce; int /*<<< orphan*/ * call_id; void* securityIndex; int /*<<< orphan*/  cid; int /*<<< orphan*/  epoch; } ;
struct rxkad_response {void* ticket_len; void* kvno; TYPE_3__ encrypted; scalar_t__ version; } ;
struct rxkad_challenge {int /*<<< orphan*/  min_level; int /*<<< orphan*/  nonce; int /*<<< orphan*/  version; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  challenge ;
struct TYPE_9__ {struct rxrpc_key_token* data; } ;
struct TYPE_14__ {TYPE_1__ payload; } ;
struct TYPE_13__ {scalar_t__ kvno; scalar_t__ ticket_len; } ;
struct TYPE_10__ {int /*<<< orphan*/  call_id; } ;

/* Variables and functions */
 int EPROTO ; 
 scalar_t__ RXKADEXPIRED ; 
 scalar_t__ RXKADINCONSISTENCY ; 
 scalar_t__ RXKADLEVELFAIL ; 
 scalar_t__ RXKADPACKETSHORT ; 
 scalar_t__ RXKAD_VERSION ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 int /*<<< orphan*/  _proto (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 void* htonl (scalar_t__) ; 
 int /*<<< orphan*/  key_serial (TYPE_7__*) ; 
 int key_validate (TYPE_7__*) ; 
 int /*<<< orphan*/  memset (struct rxkad_response*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxkad_calc_response_checksum (struct rxkad_response*) ; 
 int /*<<< orphan*/  rxkad_encrypt_response (struct rxrpc_connection*,struct rxkad_response*,TYPE_5__*) ; 
 int rxkad_send_response (struct rxrpc_connection*,TYPE_4__*,struct rxkad_response*,TYPE_5__*) ; 
 struct rxrpc_skb_priv* rxrpc_skb (struct sk_buff*) ; 
 scalar_t__ skb_copy_bits (struct sk_buff*,int /*<<< orphan*/ ,struct rxkad_challenge*,int) ; 

__attribute__((used)) static int rxkad_respond_to_challenge(struct rxrpc_connection *conn,
				      struct sk_buff *skb,
				      u32 *_abort_code)
{
	const struct rxrpc_key_token *token;
	struct rxkad_challenge challenge;
	struct rxkad_response resp
		__attribute__((aligned(8))); /* must be aligned for crypto */
	struct rxrpc_skb_priv *sp;
	u32 version, nonce, min_level, abort_code;
	int ret;

	_enter("{%d,%x}", conn->debug_id, key_serial(conn->key));

	if (!conn->key) {
		_leave(" = -EPROTO [no key]");
		return -EPROTO;
	}

	ret = key_validate(conn->key);
	if (ret < 0) {
		*_abort_code = RXKADEXPIRED;
		return ret;
	}

	abort_code = RXKADPACKETSHORT;
	sp = rxrpc_skb(skb);
	if (skb_copy_bits(skb, 0, &challenge, sizeof(challenge)) < 0)
		goto protocol_error;

	version = ntohl(challenge.version);
	nonce = ntohl(challenge.nonce);
	min_level = ntohl(challenge.min_level);

	_proto("Rx CHALLENGE %%%u { v=%u n=%u ml=%u }",
	       ntohl(sp->hdr.serial), version, nonce, min_level);

	abort_code = RXKADINCONSISTENCY;
	if (version != RXKAD_VERSION)
		goto protocol_error;

	abort_code = RXKADLEVELFAIL;
	if (conn->security_level < min_level)
		goto protocol_error;

	token = conn->key->payload.data;

	/* build the response packet */
	memset(&resp, 0, sizeof(resp));

	resp.version = RXKAD_VERSION;
	resp.encrypted.epoch = conn->epoch;
	resp.encrypted.cid = conn->cid;
	resp.encrypted.securityIndex = htonl(conn->security_ix);
	resp.encrypted.call_id[0] =
		(conn->channels[0] ? conn->channels[0]->call_id : 0);
	resp.encrypted.call_id[1] =
		(conn->channels[1] ? conn->channels[1]->call_id : 0);
	resp.encrypted.call_id[2] =
		(conn->channels[2] ? conn->channels[2]->call_id : 0);
	resp.encrypted.call_id[3] =
		(conn->channels[3] ? conn->channels[3]->call_id : 0);
	resp.encrypted.inc_nonce = htonl(nonce + 1);
	resp.encrypted.level = htonl(conn->security_level);
	resp.kvno = htonl(token->kad->kvno);
	resp.ticket_len = htonl(token->kad->ticket_len);

	/* calculate the response checksum and then do the encryption */
	rxkad_calc_response_checksum(&resp);
	rxkad_encrypt_response(conn, &resp, token->kad);
	return rxkad_send_response(conn, &sp->hdr, &resp, token->kad);

protocol_error:
	*_abort_code = abort_code;
	_leave(" = -EPROTO [%d]", abort_code);
	return -EPROTO;
}