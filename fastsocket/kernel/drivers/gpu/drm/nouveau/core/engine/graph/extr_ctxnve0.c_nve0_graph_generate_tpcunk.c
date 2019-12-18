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
nve0_graph_generate_tpcunk(struct nvc0_graph_priv *priv)
{
	nv_wr32(priv, 0x41be24, 0x6);
	nv_wr32(priv, 0x41bec0, 0x12180000);
	nv_wr32(priv, 0x41bec4, 0x37f7f);
	nv_wr32(priv, 0x41bee4, 0x6480430);
	nv_wr32(priv, 0x41bf00, 0xa418820);
	nv_wr32(priv, 0x41bf04, 0x62080e6);
	nv_wr32(priv, 0x41bf08, 0x20398a4);
	nv_wr32(priv, 0x41bf0c, 0xe629062);
	nv_wr32(priv, 0x41bf10, 0xa418820);
	nv_wr32(priv, 0x41bf14, 0xe6);
	nv_wr32(priv, 0x41bfd0, 0x900103);
	nv_wr32(priv, 0x41bfe0, 0x400001);
	nv_wr32(priv, 0x41bfe4, 0x0);
}