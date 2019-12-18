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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN (int,int) ; 
 int /*<<< orphan*/  __VIWriteI2CRegisterBuf (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** gamma_coeffs ; 

void VIDEO_SetGamma(int gamma)
{
   gamma = MAX(0,MIN(30,gamma));
   u8 *data = (u8 *)&gamma_coeffs[gamma][0];
   __VIWriteI2CRegisterBuf(0x10, 0x21, data);
}