#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_2__ {int len; int /*<<< orphan*/ * text; int /*<<< orphan*/  round; } ;
typedef  int /*<<< orphan*/  BT_OCTET16 ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int BT_OCTET16_LEN ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SMP_TRACE_DEBUG (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMP_TRACE_EVENT (char*) ; 
 scalar_t__ TRUE ; 
 TYPE_1__ cmac_cb ; 
 int /*<<< orphan*/  padding (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_xor_128 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmac_prepare_last_block (BT_OCTET16 k1, BT_OCTET16 k2)
{
//    UINT8       x[16] = {0};
    BOOLEAN      flag;

    SMP_TRACE_EVENT ("cmac_prepare_last_block ");
    /* last block is a complete block set flag to 1 */
    flag = ((cmac_cb.len % BT_OCTET16_LEN) == 0 && cmac_cb.len != 0)  ? TRUE : FALSE;

    SMP_TRACE_DEBUG("flag = %d round = %d", flag, cmac_cb.round);

    if ( flag ) {
        /* last block is complete block */
        smp_xor_128(&cmac_cb.text[0], k1);
    } else { /* padding then xor with k2 */
        padding(&cmac_cb.text[0], (UINT8)(cmac_cb.len % 16));

        smp_xor_128(&cmac_cb.text[0], k2);
    }
}