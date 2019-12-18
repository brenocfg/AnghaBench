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
struct TYPE_2__ {scalar_t__ bgm_volume; } ;

/* Variables and functions */
 int /*<<< orphan*/  SetVolumeOgg (int) ; 
 TYPE_1__ config ; 

__attribute__((used)) static void update_bgm(void)
{
  SetVolumeOgg(((int)config.bgm_volume * 255) / 100);
}