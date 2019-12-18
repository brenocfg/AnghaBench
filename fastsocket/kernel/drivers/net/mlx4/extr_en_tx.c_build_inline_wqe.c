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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int len; } ;
struct mlx4_wqe_inline_seg {void* byte_count; } ;
struct mlx4_en_tx_desc {struct mlx4_wqe_inline_seg inl; } ;
struct TYPE_4__ {TYPE_1__* frags; scalar_t__ nr_frags; } ;
struct TYPE_3__ {int size; } ;

/* Variables and functions */
 int CTRL_SIZE ; 
 int MLX4_INLINE_ALIGN ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,struct mlx4_wqe_inline_seg*,int) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data_offset (struct sk_buff*,int,struct mlx4_wqe_inline_seg*,int) ; 
 int skb_headlen (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void build_inline_wqe(struct mlx4_en_tx_desc *tx_desc, struct sk_buff *skb,
			     int real_size, u16 *vlan_tag, int tx_ind, void *fragptr)
{
	struct mlx4_wqe_inline_seg *inl = &tx_desc->inl;
	int spc = MLX4_INLINE_ALIGN - CTRL_SIZE - sizeof *inl;

	if (skb->len <= spc) {
		inl->byte_count = cpu_to_be32(1 << 31 | skb->len);
		skb_copy_from_linear_data(skb, inl + 1, skb_headlen(skb));
		if (skb_shinfo(skb)->nr_frags)
			memcpy(((void *)(inl + 1)) + skb_headlen(skb), fragptr,
			       skb_shinfo(skb)->frags[0].size);

	} else {
		inl->byte_count = cpu_to_be32(1 << 31 | spc);
		if (skb_headlen(skb) <= spc) {
			skb_copy_from_linear_data(skb, inl + 1, skb_headlen(skb));
			if (skb_headlen(skb) < spc) {
				memcpy(((void *)(inl + 1)) + skb_headlen(skb),
					fragptr, spc - skb_headlen(skb));
				fragptr +=  spc - skb_headlen(skb);
			}
			inl = (void *) (inl + 1) + spc;
			memcpy(((void *)(inl + 1)), fragptr, skb->len - spc);
		} else {
			skb_copy_from_linear_data(skb, inl + 1, spc);
			inl = (void *) (inl + 1) + spc;
			skb_copy_from_linear_data_offset(skb, spc, inl + 1,
					skb_headlen(skb) - spc);
			if (skb_shinfo(skb)->nr_frags)
				memcpy(((void *)(inl + 1)) + skb_headlen(skb) - spc,
					fragptr, skb_shinfo(skb)->frags[0].size);
		}

		wmb();
		inl->byte_count = cpu_to_be32(1 << 31 | (skb->len - spc));
	}
}