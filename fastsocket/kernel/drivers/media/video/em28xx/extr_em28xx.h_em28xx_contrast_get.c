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
struct em28xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EM28XX_R20_YGAIN ; 
 int em28xx_read_reg (struct em28xx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int em28xx_contrast_get(struct em28xx *dev)
{
	return em28xx_read_reg(dev, EM28XX_R20_YGAIN) & 0x1f;
}