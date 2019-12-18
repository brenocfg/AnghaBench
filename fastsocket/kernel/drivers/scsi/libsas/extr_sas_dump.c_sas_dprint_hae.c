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
struct sas_ha_struct {int /*<<< orphan*/  dev; } ;
typedef  enum ha_event { ____Placeholder_ha_event } ha_event ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_DPRINTK (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sas_hae_str ; 

void sas_dprint_hae(struct sas_ha_struct *sas_ha, enum ha_event he)
{
	SAS_DPRINTK("ha %s: %s event\n", dev_name(sas_ha->dev),
		    sas_hae_str[he]);
}