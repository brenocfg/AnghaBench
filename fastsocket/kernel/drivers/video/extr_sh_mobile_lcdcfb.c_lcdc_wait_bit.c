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
struct sh_mobile_lcdc_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long lcdc_read (struct sh_mobile_lcdc_priv*,unsigned long) ; 

__attribute__((used)) static void lcdc_wait_bit(struct sh_mobile_lcdc_priv *priv,
			  unsigned long reg_offs,
			  unsigned long mask, unsigned long until)
{
	while ((lcdc_read(priv, reg_offs) & mask) != until)
		cpu_relax();
}