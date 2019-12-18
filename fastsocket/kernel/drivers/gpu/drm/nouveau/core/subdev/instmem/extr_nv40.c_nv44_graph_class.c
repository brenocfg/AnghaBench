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
struct nv04_instmem_priv {int dummy; } ;
struct TYPE_2__ {int chipset; } ;

/* Variables and functions */
 TYPE_1__* nv_device (struct nv04_instmem_priv*) ; 

__attribute__((used)) static inline int
nv44_graph_class(struct nv04_instmem_priv *priv)
{
	if ((nv_device(priv)->chipset & 0xf0) == 0x60)
		return 1;
	return !(0x0baf & (1 << (nv_device(priv)->chipset & 0x0f)));
}