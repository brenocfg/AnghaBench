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
typedef  char u8 ;
typedef  int u32 ;
struct usbnet {int /*<<< orphan*/  net; } ;
struct ndis_config_param {void* value_length; void* value_offs; void* type; void* name_length; void* name_offs; } ;
typedef  void* __le32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OID_GEN_RNDIS_CONFIG_PARAMETER ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (char) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  kfree (struct ndis_config_param*) ; 
 struct ndis_config_param* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ndis_config_param*,int,int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int rndis_set_oid (struct usbnet*,int /*<<< orphan*/ ,struct ndis_config_param*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static int rndis_set_config_parameter(struct usbnet *dev, char *param,
						int value_type, void *value)
{
	struct ndis_config_param *infobuf;
	int value_len, info_len, param_len, ret, i;
	__le16 *unibuf;
	__le32 *dst_value;

	if (value_type == 0)
		value_len = sizeof(__le32);
	else if (value_type == 2)
		value_len = strlen(value) * sizeof(__le16);
	else
		return -EINVAL;

	param_len = strlen(param) * sizeof(__le16);
	info_len = sizeof(*infobuf) + param_len + value_len;

#ifdef DEBUG
	info_len += 12;
#endif
	infobuf = kmalloc(info_len, GFP_KERNEL);
	if (!infobuf)
		return -ENOMEM;

#ifdef DEBUG
	info_len -= 12;
	/* extra 12 bytes are for padding (debug output) */
	memset(infobuf, 0xCC, info_len + 12);
#endif

	if (value_type == 2)
		netdev_dbg(dev->net, "setting config parameter: %s, value: %s\n",
			   param, (u8 *)value);
	else
		netdev_dbg(dev->net, "setting config parameter: %s, value: %d\n",
			   param, *(u32 *)value);

	infobuf->name_offs = cpu_to_le32(sizeof(*infobuf));
	infobuf->name_length = cpu_to_le32(param_len);
	infobuf->type = cpu_to_le32(value_type);
	infobuf->value_offs = cpu_to_le32(sizeof(*infobuf) + param_len);
	infobuf->value_length = cpu_to_le32(value_len);

	/* simple string to unicode string conversion */
	unibuf = (void *)infobuf + sizeof(*infobuf);
	for (i = 0; i < param_len / sizeof(__le16); i++)
		unibuf[i] = cpu_to_le16(param[i]);

	if (value_type == 2) {
		unibuf = (void *)infobuf + sizeof(*infobuf) + param_len;
		for (i = 0; i < value_len / sizeof(__le16); i++)
			unibuf[i] = cpu_to_le16(((u8 *)value)[i]);
	} else {
		dst_value = (void *)infobuf + sizeof(*infobuf) + param_len;
		*dst_value = cpu_to_le32(*(u32 *)value);
	}

#ifdef DEBUG
	netdev_dbg(dev->net, "info buffer (len: %d)\n", info_len);
	for (i = 0; i < info_len; i += 12) {
		u32 *tmp = (u32 *)((u8 *)infobuf + i);
		netdev_dbg(dev->net, "%08X:%08X:%08X\n",
			   cpu_to_be32(tmp[0]),
			   cpu_to_be32(tmp[1]),
			   cpu_to_be32(tmp[2]));
	}
#endif

	ret = rndis_set_oid(dev, OID_GEN_RNDIS_CONFIG_PARAMETER,
							infobuf, info_len);
	if (ret != 0)
		netdev_dbg(dev->net, "setting rndis config parameter failed, %d\n",
			   ret);

	kfree(infobuf);
	return ret;
}