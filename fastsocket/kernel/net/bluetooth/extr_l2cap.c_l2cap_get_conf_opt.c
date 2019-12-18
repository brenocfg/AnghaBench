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
typedef  unsigned long u8 ;
struct l2cap_conf_opt {int len; int type; scalar_t__ val; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int,int,unsigned long) ; 
 int L2CAP_CONF_OPT_SIZE ; 
 unsigned long __le16_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned long __le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int l2cap_get_conf_opt(void **ptr, int *type, int *olen, unsigned long *val)
{
	struct l2cap_conf_opt *opt = *ptr;
	int len;

	len = L2CAP_CONF_OPT_SIZE + opt->len;
	*ptr += len;

	*type = opt->type;
	*olen = opt->len;

	switch (opt->len) {
	case 1:
		*val = *((u8 *) opt->val);
		break;

	case 2:
		*val = __le16_to_cpu(*((__le16 *) opt->val));
		break;

	case 4:
		*val = __le32_to_cpu(*((__le32 *) opt->val));
		break;

	default:
		*val = (unsigned long) opt->val;
		break;
	}

	BT_DBG("type 0x%2.2x len %d val 0x%lx", *type, opt->len, *val);
	return len;
}