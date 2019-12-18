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
struct i2400m_tlv_hdr {int /*<<< orphan*/  length; } ;
struct i2400m_l3l4_hdr {void* version; void* length; void* type; } ;
struct i2400m {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  strerr ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int I2400M_L3L4_VERSION ; 
 unsigned int I2400M_MT_SET_INIT_CONFIG ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 void* cpu_to_le16 (unsigned int) ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct i2400m*,struct i2400m_tlv_hdr const**,size_t,int) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct i2400m*,struct i2400m_tlv_hdr const**,size_t) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int,...) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 int i2400m_msg_check_status (int /*<<< orphan*/ ,char*,int) ; 
 struct sk_buff* i2400m_msg_to_dev (struct i2400m*,void*,int) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,struct i2400m_tlv_hdr const*,unsigned int) ; 
 int /*<<< orphan*/  wimax_msg_data (struct sk_buff*) ; 

int i2400m_set_init_config(struct i2400m *i2400m,
			   const struct i2400m_tlv_hdr **arg, size_t args)
{
	int result;
	struct device *dev = i2400m_dev(i2400m);
	struct sk_buff *ack_skb;
	struct i2400m_l3l4_hdr *cmd;
	char strerr[32];
	unsigned argc, argsize, tlv_size;
	const struct i2400m_tlv_hdr *tlv_hdr;
	void *buf, *itr;

	d_fnstart(3, dev, "(i2400m %p arg %p args %zu)\n", i2400m, arg, args);
	result = 0;
	if (args == 0)
		goto none;
	/* Compute the size of all the TLVs, so we can alloc a
	 * contiguous command block to copy them. */
	argsize = 0;
	for (argc = 0; argc < args; argc++) {
		tlv_hdr = arg[argc];
		argsize += sizeof(*tlv_hdr) + le16_to_cpu(tlv_hdr->length);
	}
	WARN_ON(argc >= 9);	/* As per hw spec */

	/* Alloc the space for the command and TLVs*/
	result = -ENOMEM;
	buf = kzalloc(sizeof(*cmd) + argsize, GFP_KERNEL);
	if (buf == NULL)
		goto error_alloc;
	cmd = buf;
	cmd->type = cpu_to_le16(I2400M_MT_SET_INIT_CONFIG);
	cmd->length = cpu_to_le16(argsize);
	cmd->version = cpu_to_le16(I2400M_L3L4_VERSION);

	/* Copy the TLVs */
	itr = buf + sizeof(*cmd);
	for (argc = 0; argc < args; argc++) {
		tlv_hdr = arg[argc];
		tlv_size = sizeof(*tlv_hdr) + le16_to_cpu(tlv_hdr->length);
		memcpy(itr, tlv_hdr, tlv_size);
		itr += tlv_size;
	}

	/* Send the message! */
	ack_skb = i2400m_msg_to_dev(i2400m, buf, sizeof(*cmd) + argsize);
	result = PTR_ERR(ack_skb);
	if (IS_ERR(ack_skb)) {
		dev_err(dev, "Failed to issue 'init config' command: %d\n",
			result);

		goto error_msg_to_dev;
	}
	result = i2400m_msg_check_status(wimax_msg_data(ack_skb),
					 strerr, sizeof(strerr));
	if (result < 0)
		dev_err(dev, "'init config' (0x%04x) command failed: %d - %s\n",
			I2400M_MT_SET_INIT_CONFIG, result, strerr);
	kfree_skb(ack_skb);
error_msg_to_dev:
	kfree(buf);
error_alloc:
none:
	d_fnend(3, dev, "(i2400m %p arg %p args %zu) = %d\n",
		i2400m, arg, args, result);
	return result;

}