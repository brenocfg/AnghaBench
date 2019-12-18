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
struct talitos_private {int desc_types; int exec_units; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int DESC_TYPE (int /*<<< orphan*/ ) ; 
 int PRIMARY_EU (int /*<<< orphan*/ ) ; 
 int SECONDARY_EU (int /*<<< orphan*/ ) ; 
 struct talitos_private* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int hw_supports(struct device *dev, __be32 desc_hdr_template)
{
	struct talitos_private *priv = dev_get_drvdata(dev);
	int ret;

	ret = (1 << DESC_TYPE(desc_hdr_template) & priv->desc_types) &&
	      (1 << PRIMARY_EU(desc_hdr_template) & priv->exec_units);

	if (SECONDARY_EU(desc_hdr_template))
		ret = ret && (1 << SECONDARY_EU(desc_hdr_template)
		              & priv->exec_units);

	return ret;
}