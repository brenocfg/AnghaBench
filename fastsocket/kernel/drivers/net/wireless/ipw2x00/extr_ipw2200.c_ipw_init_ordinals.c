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
struct ipw_priv {int table0_len; int table1_len; int table2_len; void* table2_addr; void* table1_addr; void* table0_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_ORD (char*,void*,int) ; 
 void* IPW_ORDINALS_TABLE_1 ; 
 void* IPW_ORDINALS_TABLE_2 ; 
 void* IPW_ORDINALS_TABLE_LOWER ; 
 void* ipw_read32 (struct ipw_priv*,void*) ; 
 void* ipw_read_reg32 (struct ipw_priv*,void*) ; 

__attribute__((used)) static void ipw_init_ordinals(struct ipw_priv *priv)
{
	priv->table0_addr = IPW_ORDINALS_TABLE_LOWER;
	priv->table0_len = ipw_read32(priv, priv->table0_addr);

	IPW_DEBUG_ORD("table 0 offset at 0x%08x, len = %i\n",
		      priv->table0_addr, priv->table0_len);

	priv->table1_addr = ipw_read32(priv, IPW_ORDINALS_TABLE_1);
	priv->table1_len = ipw_read_reg32(priv, priv->table1_addr);

	IPW_DEBUG_ORD("table 1 offset at 0x%08x, len = %i\n",
		      priv->table1_addr, priv->table1_len);

	priv->table2_addr = ipw_read32(priv, IPW_ORDINALS_TABLE_2);
	priv->table2_len = ipw_read_reg32(priv, priv->table2_addr);
	priv->table2_len &= 0x0000ffff;	/* use first two bytes */

	IPW_DEBUG_ORD("table 2 offset at 0x%08x, len = %i\n",
		      priv->table2_addr, priv->table2_len);

}