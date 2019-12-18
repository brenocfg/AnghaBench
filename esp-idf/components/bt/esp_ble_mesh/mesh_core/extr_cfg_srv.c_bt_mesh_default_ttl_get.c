#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8_t ;
struct TYPE_2__ {int /*<<< orphan*/  default_ttl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_TTL ; 
 TYPE_1__* conf ; 

u8_t bt_mesh_default_ttl_get(void)
{
    if (conf) {
        return conf->default_ttl;
    }

    return DEFAULT_TTL;
}