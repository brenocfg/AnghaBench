#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  quality; } ;
struct TYPE_4__ {scalar_t__ mchip_mmregs; TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ MCHIP_VRJ_TABLE_DATA ; 
 int /*<<< orphan*/ * jpeg_huffman_tables (int*) ; 
 int /*<<< orphan*/ * jpeg_quantisation_tables (int*,int /*<<< orphan*/ ) ; 
 TYPE_2__ meye ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mchip_load_tables(void)
{
	int i;
	int length;
	u16 *tables;

	tables = jpeg_huffman_tables(&length);
	for (i = 0; i < length; i++)
		writel(tables[i], meye.mchip_mmregs + MCHIP_VRJ_TABLE_DATA);

	tables = jpeg_quantisation_tables(&length, meye.params.quality);
	for (i = 0; i < length; i++)
		writel(tables[i], meye.mchip_mmregs + MCHIP_VRJ_TABLE_DATA);
}