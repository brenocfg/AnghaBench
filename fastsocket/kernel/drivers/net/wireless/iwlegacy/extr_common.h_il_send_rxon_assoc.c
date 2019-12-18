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
struct il_priv {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* rxon_assoc ) (struct il_priv*) ;} ;

/* Variables and functions */
 int stub1 (struct il_priv*) ; 

__attribute__((used)) static inline int
il_send_rxon_assoc(struct il_priv *il)
{
	return il->ops->rxon_assoc(il);
}