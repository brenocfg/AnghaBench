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
typedef  int /*<<< orphan*/  u32 ;
struct efx_channel {int /*<<< orphan*/  channel; int /*<<< orphan*/  efx; } ;
typedef  int /*<<< orphan*/  efx_qword_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_POPULATE_QWORD_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSE_AZ_EV_CODE_DRV_GEN_EV ; 
 int /*<<< orphan*/  FSF_AZ_DRV_GEN_EV_MAGIC ; 
 int /*<<< orphan*/  FSF_AZ_EV_CODE ; 
 int /*<<< orphan*/  efx_generate_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void efx_magic_event(struct efx_channel *channel, u32 magic)
{
	efx_qword_t event;

	EFX_POPULATE_QWORD_2(event, FSF_AZ_EV_CODE,
			     FSE_AZ_EV_CODE_DRV_GEN_EV,
			     FSF_AZ_DRV_GEN_EV_MAGIC, magic);
	efx_generate_event(channel->efx, channel->channel, &event);
}