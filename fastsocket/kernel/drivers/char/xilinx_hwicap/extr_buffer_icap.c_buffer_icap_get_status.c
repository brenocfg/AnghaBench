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
struct hwicap_drvdata {scalar_t__ base_address; } ;

/* Variables and functions */
 scalar_t__ XHI_STATUS_REG_OFFSET ; 
 int /*<<< orphan*/  in_be32 (scalar_t__) ; 

u32 buffer_icap_get_status(struct hwicap_drvdata *drvdata)
{
	return in_be32(drvdata->base_address + XHI_STATUS_REG_OFFSET);
}