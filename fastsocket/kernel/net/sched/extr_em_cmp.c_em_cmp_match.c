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
typedef  unsigned char u32 ;
struct tcf_pkt_info {int dummy; } ;
struct tcf_ematch {scalar_t__ data; } ;
struct tcf_em_cmp {int off; int align; int mask; int opnd; unsigned char val; int /*<<< orphan*/  layer; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
#define  TCF_EM_ALIGN_U16 133 
#define  TCF_EM_ALIGN_U32 132 
#define  TCF_EM_ALIGN_U8 131 
#define  TCF_EM_OPND_EQ 130 
#define  TCF_EM_OPND_GT 129 
#define  TCF_EM_OPND_LT 128 
 unsigned char be16_to_cpu (unsigned char) ; 
 unsigned char be32_to_cpu (unsigned char) ; 
 int /*<<< orphan*/  cmp_needs_transformation (struct tcf_em_cmp*) ; 
 unsigned char get_unaligned_be16 (unsigned char*) ; 
 unsigned char get_unaligned_be32 (unsigned char*) ; 
 unsigned char* tcf_get_base_ptr (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_valid_offset (struct sk_buff*,unsigned char*,int) ; 

__attribute__((used)) static int em_cmp_match(struct sk_buff *skb, struct tcf_ematch *em,
			struct tcf_pkt_info *info)
{
	struct tcf_em_cmp *cmp = (struct tcf_em_cmp *) em->data;
	unsigned char *ptr = tcf_get_base_ptr(skb, cmp->layer) + cmp->off;
	u32 val = 0;

	if (!tcf_valid_offset(skb, ptr, cmp->align))
		return 0;

	switch (cmp->align) {
		case TCF_EM_ALIGN_U8:
			val = *ptr;
			break;

		case TCF_EM_ALIGN_U16:
			val = get_unaligned_be16(ptr);

			if (cmp_needs_transformation(cmp))
				val = be16_to_cpu(val);
			break;

		case TCF_EM_ALIGN_U32:
			/* Worth checking boundries? The branching seems
			 * to get worse. Visit again. */
			val = get_unaligned_be32(ptr);

			if (cmp_needs_transformation(cmp))
				val = be32_to_cpu(val);
			break;

		default:
			return 0;
	}

	if (cmp->mask)
		val &= cmp->mask;

	switch (cmp->opnd) {
		case TCF_EM_OPND_EQ:
			return val == cmp->val;
		case TCF_EM_OPND_LT:
			return val < cmp->val;
		case TCF_EM_OPND_GT:
			return val > cmp->val;
	}

	return 0;
}