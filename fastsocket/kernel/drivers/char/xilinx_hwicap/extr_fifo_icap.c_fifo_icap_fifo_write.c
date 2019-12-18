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
struct hwicap_drvdata {scalar_t__ base_address; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ XHI_WF_OFFSET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_be32 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void fifo_icap_fifo_write(struct hwicap_drvdata *drvdata,
		u32 data)
{
	dev_dbg(drvdata->dev, "fifo_write: %x\n", data);
	out_be32(drvdata->base_address + XHI_WF_OFFSET, data);
}