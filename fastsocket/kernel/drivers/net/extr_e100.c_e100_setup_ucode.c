#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct sk_buff {int dummy; } ;
struct nic {int dummy; } ;
struct firmware {size_t* data; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ucode; } ;
struct cb {int /*<<< orphan*/  command; TYPE_1__ u; int /*<<< orphan*/ * skb; } ;

/* Variables and functions */
 int BUNDLEMAX ; 
 scalar_t__ BUNDLESMALL ; 
 int INTDELAY ; 
 int UCODE_SIZE ; 
 int cb_el ; 
 int cb_ucode ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,size_t*,int) ; 

__attribute__((used)) static void e100_setup_ucode(struct nic *nic, struct cb *cb,
			     struct sk_buff *skb)
{
	const struct firmware *fw = (void *)skb;
	u8 timer, bundle, min_size;

	/* It's not a real skb; we just abused the fact that e100_exec_cb
	   will pass it through to here... */
	cb->skb = NULL;

	/* firmware is stored as little endian already */
	memcpy(cb->u.ucode, fw->data, UCODE_SIZE * 4);

	/* Read timer, bundle and min_size from end of firmware blob */
	timer = fw->data[UCODE_SIZE * 4];
	bundle = fw->data[UCODE_SIZE * 4 + 1];
	min_size = fw->data[UCODE_SIZE * 4 + 2];

	/* Insert user-tunable settings in cb->u.ucode */
	cb->u.ucode[timer] &= cpu_to_le32(0xFFFF0000);
	cb->u.ucode[timer] |= cpu_to_le32(INTDELAY);
	cb->u.ucode[bundle] &= cpu_to_le32(0xFFFF0000);
	cb->u.ucode[bundle] |= cpu_to_le32(BUNDLEMAX);
	cb->u.ucode[min_size] &= cpu_to_le32(0xFFFF0000);
	cb->u.ucode[min_size] |= cpu_to_le32((BUNDLESMALL) ? 0xFFFF : 0xFF80);

	cb->command = cpu_to_le16(cb_ucode | cb_el);
}