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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_TO_BDADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btm_sec_pin_code_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2c_pin_code_request (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btu_hcif_pin_code_request_evt (UINT8 *p)
{
#if (CLASSIC_BT_INCLUDED == TRUE)
    BD_ADDR  bda;

    STREAM_TO_BDADDR (bda, p);

    /* Tell L2CAP that there was a PIN code request,  */
    /* it may need to stretch timeouts                */
    l2c_pin_code_request (bda);

    btm_sec_pin_code_request (bda);
#endif  ///CLASSIC_BT_INCLUDED == TRUE
}