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
typedef  int u8 ;
struct ipw_priv {int status; int /*<<< orphan*/  indirect_byte; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int STATUS_INDIRECT_BYTE ; 
 struct ipw_priv* dev_get_drvdata (struct device*) ; 
 int ipw_read_reg8 (struct ipw_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_indirect_byte(struct device *d,
				  struct device_attribute *attr, char *buf)
{
	u8 reg = 0;
	struct ipw_priv *priv = dev_get_drvdata(d);

	if (priv->status & STATUS_INDIRECT_BYTE)
		reg = ipw_read_reg8(priv, priv->indirect_byte);
	else
		reg = 0;

	return sprintf(buf, "0x%02x\n", reg);
}