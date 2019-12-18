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
struct nvc0_graph_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_mthd (struct nvc0_graph_priv*,int,int,int) ; 
 int nvc0_graph_class (struct nvc0_graph_priv*) ; 

__attribute__((used)) static void
nvc0_grctx_generate_9297(struct nvc0_graph_priv *priv)
{
	u32 fermi = nvc0_graph_class(priv);
	u32 mthd;

	if (fermi == 0x9297) {
		for (mthd = 0x3400; mthd <= 0x35fc; mthd += 4)
			nv_mthd(priv, 0x9297, mthd, 0x00000000);
	}
	nv_mthd(priv, 0x9297, 0x036c, 0x00000000);
	nv_mthd(priv, 0x9297, 0x0370, 0x00000000);
	nv_mthd(priv, 0x9297, 0x07a4, 0x00000000);
	nv_mthd(priv, 0x9297, 0x07a8, 0x00000000);
	nv_mthd(priv, 0x9297, 0x0374, 0x00000000);
	nv_mthd(priv, 0x9297, 0x0378, 0x00000020);
}