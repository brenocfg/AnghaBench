#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* dev_ops; } ;
struct intel_dvo {TYPE_2__ dev; } ;
struct intel_connector {int /*<<< orphan*/  base; } ;
struct TYPE_3__ {int (* get_hw_state ) (TYPE_2__*) ;} ;

/* Variables and functions */
 struct intel_dvo* intel_attached_dvo (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_2__*) ; 

__attribute__((used)) static bool intel_dvo_connector_get_hw_state(struct intel_connector *connector)
{
	struct intel_dvo *intel_dvo = intel_attached_dvo(&connector->base);

	return intel_dvo->dev.dev_ops->get_hw_state(&intel_dvo->dev);
}