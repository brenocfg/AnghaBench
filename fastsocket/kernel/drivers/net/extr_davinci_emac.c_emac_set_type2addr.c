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
typedef  int u32 ;
struct emac_priv {int dummy; } ;

/* Variables and functions */
 char BIT (int) ; 
 int /*<<< orphan*/  EMAC_MACADDRHI ; 
 int /*<<< orphan*/  EMAC_MACADDRLO ; 
 int /*<<< orphan*/  EMAC_MACINDEX ; 
 int /*<<< orphan*/  emac_set_type0addr (struct emac_priv*,int,char*) ; 
 int /*<<< orphan*/  emac_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void emac_set_type2addr(struct emac_priv *priv, u32 ch,
			       char *mac_addr, int index, int match)
{
	u32 val;
	emac_write(EMAC_MACINDEX, index);
	val = ((mac_addr[3] << 24) | (mac_addr[2] << 16) | \
	       (mac_addr[1] << 8) | (mac_addr[0]));
	emac_write(EMAC_MACADDRHI, val);
	val = ((mac_addr[5] << 8) | mac_addr[4] | ((ch & 0x7) << 16) | \
	       (match << 19) | BIT(20));
	emac_write(EMAC_MACADDRLO, val);
	emac_set_type0addr(priv, ch, mac_addr);
}