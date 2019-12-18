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
typedef  scalar_t__ u32 ;
struct rio_priv {scalar_t__ regs_win; } ;
struct rio_mport {struct rio_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  out_be32 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int fsl_local_config_write(struct rio_mport *mport,
				int index, u32 offset, int len, u32 data)
{
	struct rio_priv *priv = mport->priv;
	pr_debug
	    ("fsl_local_config_write: index %d offset %8.8x data %8.8x\n",
	     index, offset, data);
	out_be32(priv->regs_win + offset, data);

	return 0;
}