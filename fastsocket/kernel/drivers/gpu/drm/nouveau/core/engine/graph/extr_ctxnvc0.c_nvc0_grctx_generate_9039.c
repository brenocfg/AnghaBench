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
 int /*<<< orphan*/  nv_mthd (struct nvc0_graph_priv*,int,int,int) ; 

__attribute__((used)) static void
nvc0_grctx_generate_9039(struct nvc0_graph_priv *priv)
{
	nv_mthd(priv, 0x9039, 0x030c, 0x00000000);
	nv_mthd(priv, 0x9039, 0x0310, 0x00000000);
	nv_mthd(priv, 0x9039, 0x0314, 0x00000000);
	nv_mthd(priv, 0x9039, 0x0320, 0x00000000);
	nv_mthd(priv, 0x9039, 0x0238, 0x00000000);
	nv_mthd(priv, 0x9039, 0x023c, 0x00000000);
	nv_mthd(priv, 0x9039, 0x0318, 0x00000000);
	nv_mthd(priv, 0x9039, 0x031c, 0x00000000);
}