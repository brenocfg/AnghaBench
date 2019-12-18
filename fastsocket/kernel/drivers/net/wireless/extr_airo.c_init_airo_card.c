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
struct net_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct net_device* _init_airo_card (unsigned short,int,int,int /*<<< orphan*/ *,struct device*) ; 

struct net_device *init_airo_card( unsigned short irq, int port, int is_pcmcia,
				  struct device *dmdev)
{
	return _init_airo_card ( irq, port, is_pcmcia, NULL, dmdev);
}