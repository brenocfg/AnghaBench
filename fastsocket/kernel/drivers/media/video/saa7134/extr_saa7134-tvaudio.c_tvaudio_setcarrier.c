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
struct saa7134_dev {int dummy; } ;

/* Variables and functions */
 int SAA7134_CARRIER1_FREQ0 ; 
 int SAA7134_CARRIER2_FREQ0 ; 
 int /*<<< orphan*/  saa_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvaudio_carr2reg (int) ; 

__attribute__((used)) static void tvaudio_setcarrier(struct saa7134_dev *dev,
			       int primary, int secondary)
{
	if (-1 == secondary)
		secondary = primary;
	saa_writel(SAA7134_CARRIER1_FREQ0 >> 2, tvaudio_carr2reg(primary));
	saa_writel(SAA7134_CARRIER2_FREQ0 >> 2, tvaudio_carr2reg(secondary));
}