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
struct nvc0_graph_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_wr32 (struct nvc0_graph_priv*,int,int) ; 

__attribute__((used)) static void
nve0_graph_generate_unk60xx(struct nvc0_graph_priv *priv)
{
	nv_wr32(priv, 0x406020, 0x4103c1);
	nv_wr32(priv, 0x406028, 0x1);
	nv_wr32(priv, 0x40602c, 0x1);
	nv_wr32(priv, 0x406030, 0x1);
	nv_wr32(priv, 0x406034, 0x1);
}