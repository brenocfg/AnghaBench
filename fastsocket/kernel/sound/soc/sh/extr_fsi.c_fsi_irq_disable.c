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
typedef  int /*<<< orphan*/  u32 ;
struct fsi_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEMSK ; 
 int /*<<< orphan*/  IMSK ; 
 int /*<<< orphan*/  fsi_master_mask_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsi_port_ab_io_bit (struct fsi_priv*,int) ; 

__attribute__((used)) static void fsi_irq_disable(struct fsi_priv *fsi, int is_play)
{
	u32 data = fsi_port_ab_io_bit(fsi, is_play);

	fsi_master_mask_set(IMSK,  data, 0);
	fsi_master_mask_set(IEMSK, data, 0);
}