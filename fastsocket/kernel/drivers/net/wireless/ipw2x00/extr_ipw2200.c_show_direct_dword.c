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
struct ipw_priv {int status; int /*<<< orphan*/  direct_dword; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int STATUS_DIRECT_DWORD ; 
 struct ipw_priv* dev_get_drvdata (struct device*) ; 
 int ipw_read32 (struct ipw_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_direct_dword(struct device *d,
				 struct device_attribute *attr, char *buf)
{
	u32 reg = 0;
	struct ipw_priv *priv = dev_get_drvdata(d);

	if (priv->status & STATUS_DIRECT_DWORD)
		reg = ipw_read32(priv, priv->direct_dword);
	else
		reg = 0;

	return sprintf(buf, "0x%08x\n", reg);
}