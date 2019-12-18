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
typedef  int /*<<< orphan*/  u8 ;
struct xfrm_state {struct ipcomp_data* data; } ;
struct sk_buff {int len; int /*<<< orphan*/ * data; } ;
struct ipcomp_data {int /*<<< orphan*/  tfms; } ;
struct ip_comp_hdr {int dummy; } ;
struct crypto_comp {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int IPCOMP_SCRATCH_SIZE ; 
 int crypto_comp_compress (struct crypto_comp*,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *,int*) ; 
 int get_cpu () ; 
 int /*<<< orphan*/  ipcomp_scratches ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void** per_cpu_ptr (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  pskb_trim (struct sk_buff*,int) ; 
 int /*<<< orphan*/  put_cpu () ; 

__attribute__((used)) static int ipcomp_compress(struct xfrm_state *x, struct sk_buff *skb)
{
	struct ipcomp_data *ipcd = x->data;
	const int plen = skb->len;
	int dlen = IPCOMP_SCRATCH_SIZE;
	u8 *start = skb->data;
	const int cpu = get_cpu();
	u8 *scratch = *per_cpu_ptr(ipcomp_scratches, cpu);
	struct crypto_comp *tfm = *per_cpu_ptr(ipcd->tfms, cpu);
	int err;

	local_bh_disable();
	err = crypto_comp_compress(tfm, start, plen, scratch, &dlen);
	local_bh_enable();
	if (err)
		goto out;

	if ((dlen + sizeof(struct ip_comp_hdr)) >= plen) {
		err = -EMSGSIZE;
		goto out;
	}

	memcpy(start + sizeof(struct ip_comp_hdr), scratch, dlen);
	put_cpu();

	pskb_trim(skb, dlen + sizeof(struct ip_comp_hdr));
	return 0;

out:
	put_cpu();
	return err;
}