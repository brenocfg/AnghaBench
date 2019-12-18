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
struct work_struct {int dummy; } ;
struct sas_ha_struct {int /*<<< orphan*/  pending; } ;
struct sas_ha_event {struct sas_ha_struct* ha; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAE_RESET ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sas_ha_event* to_sas_ha_event (struct work_struct*) ; 

void sas_hae_reset(struct work_struct *work)
{
	struct sas_ha_event *ev = to_sas_ha_event(work);
	struct sas_ha_struct *ha = ev->ha;

	clear_bit(HAE_RESET, &ha->pending);
}