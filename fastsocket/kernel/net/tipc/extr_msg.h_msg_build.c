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
typedef  int u32 ;
struct tipc_msg {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct iovec {scalar_t__ iov_len; int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int TIPC_MAX_USER_MSG_SIZE ; 
 struct sk_buff* buf_acquire (int) ; 
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 
 int /*<<< orphan*/  copy_from_user (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ likely (int) ; 
 int msg_calc_data_size (struct iovec const*,int) ; 
 int msg_hdr_sz (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_set_size (struct tipc_msg*,int) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,struct tipc_msg*,int) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data_offset (struct sk_buff*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int msg_build(struct tipc_msg *hdr,
			    struct iovec const *msg_sect, u32 num_sect,
			    int max_size, int usrmem, struct sk_buff** buf)
{
	int dsz, sz, hsz, pos, res, cnt;

	dsz = msg_calc_data_size(msg_sect, num_sect);
	if (unlikely(dsz > TIPC_MAX_USER_MSG_SIZE)) {
		*buf = NULL;
		return -EINVAL;
	}

	pos = hsz = msg_hdr_sz(hdr);
	sz = hsz + dsz;
	msg_set_size(hdr, sz);
	if (unlikely(sz > max_size)) {
		*buf = NULL;
		return dsz;
	}

	*buf = buf_acquire(sz);
	if (!(*buf))
		return -ENOMEM;
	skb_copy_to_linear_data(*buf, hdr, hsz);
	for (res = 1, cnt = 0; res && (cnt < num_sect); cnt++) {
		if (likely(usrmem))
			res = !copy_from_user((*buf)->data + pos,
					      msg_sect[cnt].iov_base,
					      msg_sect[cnt].iov_len);
		else
			skb_copy_to_linear_data_offset(*buf, pos,
						       msg_sect[cnt].iov_base,
						       msg_sect[cnt].iov_len);
		pos += msg_sect[cnt].iov_len;
	}
	if (likely(res))
		return dsz;

	buf_discard(*buf);
	*buf = NULL;
	return -EFAULT;
}