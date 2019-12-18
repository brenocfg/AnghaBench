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
struct intel_dvo_device {struct ch7xxx_priv* dev_priv; } ;
struct ch7xxx_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ch7xxx_priv*) ; 

__attribute__((used)) static void ch7xxx_destroy(struct intel_dvo_device *dvo)
{
	struct ch7xxx_priv *ch7xxx = dvo->dev_priv;

	if (ch7xxx) {
		kfree(ch7xxx);
		dvo->dev_priv = NULL;
	}
}