#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct sk_buff {int len; } ;
struct scatterlist {int dummy; } ;
struct TYPE_10__ {int seq; int callNumber; } ;
struct rxrpc_skb_priv {TYPE_5__ hdr; } ;
struct rxrpc_key_token {TYPE_3__* kad; } ;
struct rxrpc_crypt {int /*<<< orphan*/  x; } ;
struct rxrpc_call {TYPE_4__* conn; } ;
struct rxkad_level2_hdr {int data_size; } ;
struct blkcipher_desc {scalar_t__ flags; int /*<<< orphan*/  info; int /*<<< orphan*/  tfm; } ;
typedef  int /*<<< orphan*/  sechdr ;
typedef  int /*<<< orphan*/  iv ;
struct TYPE_9__ {int /*<<< orphan*/  cipher; TYPE_2__* key; } ;
struct TYPE_8__ {int /*<<< orphan*/  session_key; } ;
struct TYPE_6__ {struct rxrpc_key_token* data; } ;
struct TYPE_7__ {TYPE_1__ payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int ENOMEM ; 
 int EPROTO ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int RXKADDATALEN ; 
 int RXKADSEALEDINCON ; 
 int /*<<< orphan*/  _enter (char*,int) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 int /*<<< orphan*/  crypto_blkcipher_decrypt_iv (struct blkcipher_desc*,struct scatterlist*,struct scatterlist*,int) ; 
 int /*<<< orphan*/  kfree (struct scatterlist*) ; 
 struct scatterlist* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct rxrpc_crypt*,int /*<<< orphan*/ ,int) ; 
 int ntohl (int) ; 
 struct rxrpc_skb_priv* rxrpc_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 scalar_t__ skb_copy_bits (struct sk_buff*,int /*<<< orphan*/ ,struct rxkad_level2_hdr*,int) ; 
 int skb_cow_data (struct sk_buff*,int /*<<< orphan*/ ,struct sk_buff**) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_to_sgvec (struct sk_buff*,struct scatterlist*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int rxkad_verify_packet_encrypt(const struct rxrpc_call *call,
				       struct sk_buff *skb,
				       u32 *_abort_code)
{
	const struct rxrpc_key_token *token;
	struct rxkad_level2_hdr sechdr;
	struct rxrpc_skb_priv *sp;
	struct blkcipher_desc desc;
	struct rxrpc_crypt iv;
	struct scatterlist _sg[4], *sg;
	struct sk_buff *trailer;
	u32 data_size, buf;
	u16 check;
	int nsg;

	_enter(",{%d}", skb->len);

	sp = rxrpc_skb(skb);

	/* we want to decrypt the skbuff in-place */
	nsg = skb_cow_data(skb, 0, &trailer);
	if (nsg < 0)
		goto nomem;

	sg = _sg;
	if (unlikely(nsg > 4)) {
		sg = kmalloc(sizeof(*sg) * nsg, GFP_NOIO);
		if (!sg)
			goto nomem;
	}

	sg_init_table(sg, nsg);
	skb_to_sgvec(skb, sg, 0, skb->len);

	/* decrypt from the session key */
	token = call->conn->key->payload.data;
	memcpy(&iv, token->kad->session_key, sizeof(iv));
	desc.tfm = call->conn->cipher;
	desc.info = iv.x;
	desc.flags = 0;

	crypto_blkcipher_decrypt_iv(&desc, sg, sg, skb->len);
	if (sg != _sg)
		kfree(sg);

	/* remove the decrypted packet length */
	if (skb_copy_bits(skb, 0, &sechdr, sizeof(sechdr)) < 0)
		goto datalen_error;
	if (!skb_pull(skb, sizeof(sechdr)))
		BUG();

	buf = ntohl(sechdr.data_size);
	data_size = buf & 0xffff;

	check = buf >> 16;
	check ^= ntohl(sp->hdr.seq ^ sp->hdr.callNumber);
	check &= 0xffff;
	if (check != 0) {
		*_abort_code = RXKADSEALEDINCON;
		goto protocol_error;
	}

	/* shorten the packet to remove the padding */
	if (data_size > skb->len)
		goto datalen_error;
	else if (data_size < skb->len)
		skb->len = data_size;

	_leave(" = 0 [dlen=%x]", data_size);
	return 0;

datalen_error:
	*_abort_code = RXKADDATALEN;
protocol_error:
	_leave(" = -EPROTO");
	return -EPROTO;

nomem:
	_leave(" = -ENOMEM");
	return -ENOMEM;
}