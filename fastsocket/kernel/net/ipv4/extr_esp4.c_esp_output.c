#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_5__ {int /*<<< orphan*/  spi; } ;
struct xfrm_state {TYPE_1__ id; int /*<<< orphan*/  lock; struct xfrm_encap_tmpl* encap; struct esp_data* data; } ;
struct xfrm_encap_tmpl {int encap_type; void* encap_dport; void* encap_sport; } ;
struct udphdr {scalar_t__ check; int /*<<< orphan*/  len; void* dest; void* source; } ;
struct sk_buff {int len; scalar_t__ data; } ;
struct scatterlist {int dummy; } ;
struct ip_esp_hdr {scalar_t__ enc_data; int /*<<< orphan*/  seq_no; int /*<<< orphan*/  spi; } ;
struct esp_data {int padlen; struct crypto_aead* aead; } ;
struct crypto_aead {int dummy; } ;
struct aead_givcrypt_request {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  void* __be16 ;
struct TYPE_8__ {void* tmp; } ;
struct TYPE_6__ {int /*<<< orphan*/  output; } ;
struct TYPE_7__ {TYPE_2__ seq; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 int ENOMEM ; 
 TYPE_4__* ESP_SKB_CB (struct sk_buff*) ; 
 int IPPROTO_ESP ; 
 int IPPROTO_UDP ; 
 int NET_XMIT_DROP ; 
#define  UDP_ENCAP_ESPINUDP 129 
#define  UDP_ENCAP_ESPINUDP_NON_IKE 128 
 TYPE_3__* XFRM_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  aead_givcrypt_set_assoc (struct aead_givcrypt_request*,struct scatterlist*,int) ; 
 int /*<<< orphan*/  aead_givcrypt_set_callback (struct aead_givcrypt_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  aead_givcrypt_set_crypt (struct aead_givcrypt_request*,struct scatterlist*,struct scatterlist*,int,int*) ; 
 int /*<<< orphan*/  aead_givcrypt_set_giv (struct aead_givcrypt_request*,scalar_t__,int /*<<< orphan*/ ) ; 
 int crypto_aead_authsize (struct crypto_aead*) ; 
 int crypto_aead_blocksize (struct crypto_aead*) ; 
 int crypto_aead_givencrypt (struct aead_givcrypt_request*) ; 
 scalar_t__ crypto_aead_ivsize (struct crypto_aead*) ; 
 void* esp_alloc_tmp (struct crypto_aead*,int) ; 
 struct scatterlist* esp_givreq_sg (struct crypto_aead*,struct aead_givcrypt_request*) ; 
 int /*<<< orphan*/  esp_output_done ; 
 struct aead_givcrypt_request* esp_tmp_givreq (struct crypto_aead*,int*) ; 
 int* esp_tmp_iv (struct crypto_aead*,void*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 struct ip_esp_hdr* ip_esp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  pskb_put (struct sk_buff*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,struct ip_esp_hdr*,int) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int skb_cow_data (struct sk_buff*,int,struct sk_buff**) ; 
 int* skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int* skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_to_sgvec (struct sk_buff*,struct scatterlist*,scalar_t__,int) ; 
 scalar_t__ skb_transport_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int esp_output(struct xfrm_state *x, struct sk_buff *skb)
{
	int err;
	struct ip_esp_hdr *esph;
	struct crypto_aead *aead;
	struct aead_givcrypt_request *req;
	struct scatterlist *sg;
	struct scatterlist *asg;
	struct esp_data *esp;
	struct sk_buff *trailer;
	void *tmp;
	u8 *iv;
	u8 *tail;
	int blksize;
	int clen;
	int alen;
	int nfrags;

	/* skb is pure payload to encrypt */

	err = -ENOMEM;

	/* Round to block size */
	clen = skb->len;

	esp = x->data;
	aead = esp->aead;
	alen = crypto_aead_authsize(aead);

	blksize = ALIGN(crypto_aead_blocksize(aead), 4);
	clen = ALIGN(clen + 2, blksize);
	if (esp->padlen)
		clen = ALIGN(clen, esp->padlen);

	if ((err = skb_cow_data(skb, clen - skb->len + alen, &trailer)) < 0)
		goto error;
	nfrags = err;

	tmp = esp_alloc_tmp(aead, nfrags + 1);
	if (!tmp)
		goto error;

	iv = esp_tmp_iv(aead, tmp);
	req = esp_tmp_givreq(aead, iv);
	asg = esp_givreq_sg(aead, req);
	sg = asg + 1;

	/* Fill padding... */
	tail = skb_tail_pointer(trailer);
	do {
		int i;
		for (i=0; i<clen-skb->len - 2; i++)
			tail[i] = i + 1;
	} while (0);
	tail[clen - skb->len - 2] = (clen - skb->len) - 2;
	tail[clen - skb->len - 1] = *skb_mac_header(skb);
	pskb_put(skb, trailer, clen - skb->len + alen);

	skb_push(skb, -skb_network_offset(skb));
	esph = ip_esp_hdr(skb);
	*skb_mac_header(skb) = IPPROTO_ESP;

	/* this is non-NULL only with UDP Encapsulation */
	if (x->encap) {
		struct xfrm_encap_tmpl *encap = x->encap;
		struct udphdr *uh;
		__be32 *udpdata32;
		__be16 sport, dport;
		int encap_type;

		spin_lock_bh(&x->lock);
		sport = encap->encap_sport;
		dport = encap->encap_dport;
		encap_type = encap->encap_type;
		spin_unlock_bh(&x->lock);

		uh = (struct udphdr *)esph;
		uh->source = sport;
		uh->dest = dport;
		uh->len = htons(skb->len - skb_transport_offset(skb));
		uh->check = 0;

		switch (encap_type) {
		default:
		case UDP_ENCAP_ESPINUDP:
			esph = (struct ip_esp_hdr *)(uh + 1);
			break;
		case UDP_ENCAP_ESPINUDP_NON_IKE:
			udpdata32 = (__be32 *)(uh + 1);
			udpdata32[0] = udpdata32[1] = 0;
			esph = (struct ip_esp_hdr *)(udpdata32 + 2);
			break;
		}

		*skb_mac_header(skb) = IPPROTO_UDP;
	}

	esph->spi = x->id.spi;
	esph->seq_no = htonl(XFRM_SKB_CB(skb)->seq.output);

	sg_init_table(sg, nfrags);
	skb_to_sgvec(skb, sg,
		     esph->enc_data + crypto_aead_ivsize(aead) - skb->data,
		     clen + alen);
	sg_init_one(asg, esph, sizeof(*esph));

	aead_givcrypt_set_callback(req, 0, esp_output_done, skb);
	aead_givcrypt_set_crypt(req, sg, sg, clen, iv);
	aead_givcrypt_set_assoc(req, asg, sizeof(*esph));
	aead_givcrypt_set_giv(req, esph->enc_data,
			      XFRM_SKB_CB(skb)->seq.output);

	ESP_SKB_CB(skb)->tmp = tmp;
	err = crypto_aead_givencrypt(req);
	if (err == -EINPROGRESS)
		goto error;

	if (err == -EBUSY)
		err = NET_XMIT_DROP;

	kfree(tmp);

error:
	return err;
}