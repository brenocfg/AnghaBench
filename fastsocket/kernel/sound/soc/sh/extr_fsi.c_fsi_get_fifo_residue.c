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
struct fsi_priv {int chan; } ;

/* Variables and functions */
 int DIFF_ST ; 
 int DOFF_ST ; 
 int fsi_reg_read (struct fsi_priv*,int) ; 

__attribute__((used)) static int fsi_get_fifo_residue(struct fsi_priv *fsi, int is_play)
{
	u32 status;
	u32 reg = is_play ? DOFF_ST : DIFF_ST;
	int residue;

	status = fsi_reg_read(fsi, reg);
	residue = 0x1ff & (status >> 8);
	residue *= fsi->chan;

	return residue;
}