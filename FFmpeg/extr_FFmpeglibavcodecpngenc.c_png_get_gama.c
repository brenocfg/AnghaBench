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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum AVColorTransferCharacteristic { ____Placeholder_AVColorTransferCharacteristic } AVColorTransferCharacteristic ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WB32_PNG (int /*<<< orphan*/ *,double) ; 
 double avpriv_get_gamma_from_trc (int) ; 

__attribute__((used)) static int png_get_gama(enum AVColorTransferCharacteristic trc, uint8_t *buf)
{
    double gamma = avpriv_get_gamma_from_trc(trc);
    if (gamma <= 1e-6)
        return 0;

    AV_WB32_PNG(buf, 1.0 / gamma);
    return 1;
}