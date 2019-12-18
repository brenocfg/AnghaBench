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
nve0_graph_generate_tpc(struct nvc0_graph_priv *priv)
{
	nv_wr32(priv, 0x419848, 0x0);
	nv_wr32(priv, 0x419864, 0x129);
	nv_wr32(priv, 0x419888, 0x0);
	nv_wr32(priv, 0x419a00, 0xf0);
	nv_wr32(priv, 0x419a04, 0x1);
	nv_wr32(priv, 0x419a08, 0x21);
	nv_wr32(priv, 0x419a0c, 0x20000);
	nv_wr32(priv, 0x419a10, 0x0);
	nv_wr32(priv, 0x419a14, 0x200);
	nv_wr32(priv, 0x419a1c, 0xc000);
	nv_wr32(priv, 0x419a20, 0x800);
	nv_wr32(priv, 0x419a30, 0x1);
	nv_wr32(priv, 0x419ac4, 0x37f440);
	nv_wr32(priv, 0x419c00, 0xa);
	nv_wr32(priv, 0x419c04, 0x80000006);
	nv_wr32(priv, 0x419c08, 0x2);
	nv_wr32(priv, 0x419c20, 0x0);
	nv_wr32(priv, 0x419c24, 0x84210);
	nv_wr32(priv, 0x419c28, 0x3efbefbe);
	nv_wr32(priv, 0x419ce8, 0x0);
	nv_wr32(priv, 0x419cf4, 0x3203);
	nv_wr32(priv, 0x419e04, 0x0);
	nv_wr32(priv, 0x419e08, 0x0);
	nv_wr32(priv, 0x419e0c, 0x0);
	nv_wr32(priv, 0x419e10, 0x402);
	nv_wr32(priv, 0x419e44, 0x13eff2);
	nv_wr32(priv, 0x419e48, 0x0);
	nv_wr32(priv, 0x419e4c, 0x7f);
	nv_wr32(priv, 0x419e50, 0x0);
	nv_wr32(priv, 0x419e54, 0x0);
	nv_wr32(priv, 0x419e58, 0x0);
	nv_wr32(priv, 0x419e5c, 0x0);
	nv_wr32(priv, 0x419e60, 0x0);
	nv_wr32(priv, 0x419e64, 0x0);
	nv_wr32(priv, 0x419e68, 0x0);
	nv_wr32(priv, 0x419e6c, 0x0);
	nv_wr32(priv, 0x419e70, 0x0);
	nv_wr32(priv, 0x419e74, 0x0);
	nv_wr32(priv, 0x419e78, 0x0);
	nv_wr32(priv, 0x419e7c, 0x0);
	nv_wr32(priv, 0x419e80, 0x0);
	nv_wr32(priv, 0x419e84, 0x0);
	nv_wr32(priv, 0x419e88, 0x0);
	nv_wr32(priv, 0x419e8c, 0x0);
	nv_wr32(priv, 0x419e90, 0x0);
	nv_wr32(priv, 0x419e94, 0x0);
	nv_wr32(priv, 0x419e98, 0x0);
	nv_wr32(priv, 0x419eac, 0x1fcf);
	nv_wr32(priv, 0x419eb0, 0xd3f);
	nv_wr32(priv, 0x419ec8, 0x1304f);
	nv_wr32(priv, 0x419f30, 0x0);
	nv_wr32(priv, 0x419f34, 0x0);
	nv_wr32(priv, 0x419f38, 0x0);
	nv_wr32(priv, 0x419f3c, 0x0);
	nv_wr32(priv, 0x419f40, 0x0);
	nv_wr32(priv, 0x419f44, 0x0);
	nv_wr32(priv, 0x419f48, 0x0);
	nv_wr32(priv, 0x419f4c, 0x0);
	nv_wr32(priv, 0x419f58, 0x0);
	nv_wr32(priv, 0x419f78, 0xb);
}