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
typedef  int /*<<< orphan*/  tBTA_SET_RAND_ADDR_CBACK ;
typedef  int* BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  BTA_DmSetRandAddress (int*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  BTC_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  BTM_INVALID_STATIC_RAND_ADDR ; 
 int BT_STATIC_RAND_ADDR_MASK ; 
 int /*<<< orphan*/  btc_set_rand_addr_callback (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

__attribute__((used)) static void btc_ble_set_rand_addr (BD_ADDR rand_addr, tBTA_SET_RAND_ADDR_CBACK *p_set_rand_addr_cback)
{
    if (rand_addr != NULL) {
        /*
        A static address is a 48-bit randomly generated address and shall meet the following requirements:
        • The two most significant bits of the address shall be equal to 1
        • All bits of the random part of the address shall not be equal to 1
        • All bits of the random part of the address shall not be equal to 0
        */
        BD_ADDR invalid_rand_addr_a, invalid_rand_addr_b;
        memset(invalid_rand_addr_a, 0xff, sizeof(BD_ADDR));
        memset(invalid_rand_addr_b, 0x00, sizeof(BD_ADDR));
        invalid_rand_addr_b[0] = invalid_rand_addr_b[0] | BT_STATIC_RAND_ADDR_MASK;
        if((rand_addr[0] & BT_STATIC_RAND_ADDR_MASK) == BT_STATIC_RAND_ADDR_MASK
            && memcmp(invalid_rand_addr_a, rand_addr, BD_ADDR_LEN) != 0
            && memcmp(invalid_rand_addr_b, rand_addr, BD_ADDR_LEN) != 0){
            BTA_DmSetRandAddress(rand_addr, btc_set_rand_addr_callback);
        } else {
            btc_set_rand_addr_callback(BTM_INVALID_STATIC_RAND_ADDR);
            BTC_TRACE_ERROR("Invalid random address, the high bit should be 0b11, bits of the random part shall not be all 1 or 0");
        }
    } else {
        btc_set_rand_addr_callback(BTM_INVALID_STATIC_RAND_ADDR);
        BTC_TRACE_ERROR("Invalid random addressm, the address value is NULL");
    }
}