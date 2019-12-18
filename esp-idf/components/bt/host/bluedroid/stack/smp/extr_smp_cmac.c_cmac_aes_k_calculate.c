#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* param_buf; } ;
typedef  TYPE_1__ tSMP_ENC ;
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_5__ {scalar_t__ round; int /*<<< orphan*/ * text; } ;
typedef  int /*<<< orphan*/  BT_OCTET16 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ BT_OCTET16_LEN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SMP_Encrypt (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  SMP_TRACE_DEBUG (char*,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  SMP_TRACE_EVENT (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__ cmac_cb ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  smp_xor_128 (int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static BOOLEAN cmac_aes_k_calculate(BT_OCTET16 key, UINT8 *p_signature, UINT16 tlen)
{
    tSMP_ENC output;
    UINT8    i = 1, err = 0;
    UINT8    x[16] = {0};
    UINT8   *p_mac;

    SMP_TRACE_EVENT ("cmac_aes_k_calculate ");

    while (i <= cmac_cb.round) {
        smp_xor_128(&cmac_cb.text[(cmac_cb.round - i)*BT_OCTET16_LEN], x); /* Mi' := Mi (+) X  */

        if (!SMP_Encrypt(key, BT_OCTET16_LEN, &cmac_cb.text[(cmac_cb.round - i)*BT_OCTET16_LEN], BT_OCTET16_LEN, &output)) {
            err = 1;
            break;
        }

        memcpy(x, output.param_buf, BT_OCTET16_LEN);
        i ++;
    }

    if (!err) {
        p_mac = output.param_buf + (BT_OCTET16_LEN - tlen);
        memcpy(p_signature, p_mac, tlen);

        SMP_TRACE_DEBUG("tlen = %d p_mac = %p", tlen, p_mac);
        SMP_TRACE_DEBUG("p_mac[0] = 0x%02x p_mac[1] = 0x%02x p_mac[2] = 0x%02x p_mac[3] = 0x%02x",
                        *p_mac, *(p_mac + 1), *(p_mac + 2), *(p_mac + 3));
        SMP_TRACE_DEBUG("p_mac[4] = 0x%02x p_mac[5] = 0x%02x p_mac[6] = 0x%02x p_mac[7] = 0x%02x",
                        *(p_mac + 4), *(p_mac + 5), *(p_mac + 6), *(p_mac + 7));

        return TRUE;

    } else {
        return FALSE;
    }
}