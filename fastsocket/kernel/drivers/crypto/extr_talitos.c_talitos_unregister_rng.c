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
struct talitos_private {int /*<<< orphan*/  rng; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct talitos_private* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  hwrng_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void talitos_unregister_rng(struct device *dev)
{
	struct talitos_private *priv = dev_get_drvdata(dev);

	hwrng_unregister(&priv->rng);
}