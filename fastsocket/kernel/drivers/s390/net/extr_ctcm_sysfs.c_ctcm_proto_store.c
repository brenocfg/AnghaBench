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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ctcm_priv {int protocol; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTCM_DBF_DEV (int /*<<< orphan*/ ,struct device*,char const*) ; 
 int CTCM_PROTO_LINUX ; 
 int CTCM_PROTO_MPC ; 
 int CTCM_PROTO_OS390 ; 
 int CTCM_PROTO_S390 ; 
 size_t EINVAL ; 
 size_t ENODEV ; 
 int /*<<< orphan*/  SETUP ; 
 struct ctcm_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,int*) ; 

__attribute__((used)) static ssize_t ctcm_proto_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	int value;
	struct ctcm_priv *priv = dev_get_drvdata(dev);

	if (!priv)
		return -ENODEV;
	sscanf(buf, "%u", &value);
	if (!((value == CTCM_PROTO_S390)  ||
	      (value == CTCM_PROTO_LINUX) ||
	      (value == CTCM_PROTO_MPC) ||
	      (value == CTCM_PROTO_OS390)))
		return -EINVAL;
	priv->protocol = value;
	CTCM_DBF_DEV(SETUP, dev, buf);

	return count;
}