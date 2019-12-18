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
struct sn9c102_device {int bridge; } ;
typedef  enum sn9c102_bridge { ____Placeholder_sn9c102_bridge } sn9c102_bridge ;

/* Variables and functions */

enum sn9c102_bridge
sn9c102_get_bridge(struct sn9c102_device* cam)
{
	return cam->bridge;
}