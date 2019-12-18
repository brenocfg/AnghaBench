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
struct pcmcia_device {struct orinoco_private* priv; } ;
struct orinoco_private {int dummy; } ;

/* Variables and functions */
 int orinoco_up (struct orinoco_private*) ; 

__attribute__((used)) static int
spectrum_cs_resume(struct pcmcia_device *link)
{
	struct orinoco_private *priv = link->priv;
	int err = orinoco_up(priv);

	return err;
}