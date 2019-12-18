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
typedef  scalar_t__ u16 ;
struct xc5000_priv {int dummy; } ;

/* Variables and functions */
 int XC_RESULT_SUCCESS ; 
 int /*<<< orphan*/  XREG_FREQ_ERROR ; 
 int xc5000_readreg (struct xc5000_priv*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int xc_get_frequency_error(struct xc5000_priv *priv, u32 *freq_error_hz)
{
	int result;
	u16 regData;
	u32 tmp;

	result = xc5000_readreg(priv, XREG_FREQ_ERROR, &regData);
	if (result != XC_RESULT_SUCCESS)
		return result;

	tmp = (u32)regData;
	(*freq_error_hz) = (tmp * 15625) / 1000;
	return result;
}