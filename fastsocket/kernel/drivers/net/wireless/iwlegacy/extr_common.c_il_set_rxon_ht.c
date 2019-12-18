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
struct il_priv {int dummy; } ;
struct il_ht_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _il_set_rxon_ht (struct il_priv*,struct il_ht_config*) ; 

void
il_set_rxon_ht(struct il_priv *il, struct il_ht_config *ht_conf)
{
	_il_set_rxon_ht(il, ht_conf);
}