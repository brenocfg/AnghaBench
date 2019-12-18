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
struct TransferCharacteristics {int /*<<< orphan*/  alpha; } ;
typedef  enum AVColorTransferCharacteristic { ____Placeholder_AVColorTransferCharacteristic } AVColorTransferCharacteristic ;

/* Variables and functions */
 int AVCOL_TRC_NB ; 
 struct TransferCharacteristics* transfer_characteristics ; 

__attribute__((used)) static const struct TransferCharacteristics *
    get_transfer_characteristics(enum AVColorTransferCharacteristic trc)
{
    const struct TransferCharacteristics *coeffs;

    if (trc >= AVCOL_TRC_NB)
        return NULL;
    coeffs = &transfer_characteristics[trc];
    if (!coeffs->alpha)
        return NULL;

    return coeffs;
}