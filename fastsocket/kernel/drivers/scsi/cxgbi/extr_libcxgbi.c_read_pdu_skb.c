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
struct sk_buff {int dummy; } ;
struct iscsi_conn {int dummy; } ;

/* Variables and functions */
 int CXGBI_DBG_PDU_RX ; 
 int EFAULT ; 
 int EINVAL ; 
 int EIO ; 
#define  ISCSI_TCP_CONN_ERR 131 
#define  ISCSI_TCP_SEGMENT_DONE 130 
#define  ISCSI_TCP_SKB_DONE 129 
#define  ISCSI_TCP_SUSPENDED 128 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  iscsi_conn_printk (int /*<<< orphan*/ ,struct iscsi_conn*,char*) ; 
 int iscsi_tcp_recv_skb (struct iscsi_conn*,struct sk_buff*,unsigned int,int,int*) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct sk_buff*,unsigned int,int,int) ; 
 int /*<<< orphan*/  pr_info (char*,struct sk_buff*,unsigned int,int,...) ; 

__attribute__((used)) static inline int read_pdu_skb(struct iscsi_conn *conn,
			       struct sk_buff *skb,
			       unsigned int offset,
			       int offloaded)
{
	int status = 0;
	int bytes_read;

	bytes_read = iscsi_tcp_recv_skb(conn, skb, offset, offloaded, &status);
	switch (status) {
	case ISCSI_TCP_CONN_ERR:
		pr_info("skb 0x%p, off %u, %d, TCP_ERR.\n",
			  skb, offset, offloaded);
		return -EIO;
	case ISCSI_TCP_SUSPENDED:
		log_debug(1 << CXGBI_DBG_PDU_RX,
			"skb 0x%p, off %u, %d, TCP_SUSPEND, rc %d.\n",
			skb, offset, offloaded, bytes_read);
		/* no transfer - just have caller flush queue */
		return bytes_read;
	case ISCSI_TCP_SKB_DONE:
		pr_info("skb 0x%p, off %u, %d, TCP_SKB_DONE.\n",
			skb, offset, offloaded);
		/*
		 * pdus should always fit in the skb and we should get
		 * segment done notifcation.
		 */
		iscsi_conn_printk(KERN_ERR, conn, "Invalid pdu or skb.");
		return -EFAULT;
	case ISCSI_TCP_SEGMENT_DONE:
		log_debug(1 << CXGBI_DBG_PDU_RX,
			"skb 0x%p, off %u, %d, TCP_SEG_DONE, rc %d.\n",
			skb, offset, offloaded, bytes_read);
		return bytes_read;
	default:
		pr_info("skb 0x%p, off %u, %d, invalid status %d.\n",
			skb, offset, offloaded, status);
		return -EINVAL;
	}
}