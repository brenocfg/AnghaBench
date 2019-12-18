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
struct atmel_private {scalar_t__ current_BSS; TYPE_1__* BSSinfo; int /*<<< orphan*/  connect_to_any_BSS; } ;
struct TYPE_2__ {int channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  atmel_join_bss (struct atmel_private*,int) ; 
 int /*<<< orphan*/  atmel_scan (struct atmel_private*,int) ; 
 int retrieve_bss (struct atmel_private*) ; 

__attribute__((used)) static void restart_search(struct atmel_private *priv)
{
	int bss_index;

	if (!priv->connect_to_any_BSS) {
		atmel_scan(priv, 1);
	} else {
		priv->BSSinfo[(int)(priv->current_BSS)].channel |= 0x80;

		if ((bss_index = retrieve_bss(priv)) != -1)
			atmel_join_bss(priv, bss_index);
		else
			atmel_scan(priv, 0);
	}
}