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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  URLContext ;

/* Variables and functions */
 int /*<<< orphan*/  rtmpe8_sig (int*,int*,int const) ; 
 int /*<<< orphan*/  rtmpe9_sig (int*,int*,int const) ; 

void ff_rtmpe_encrypt_sig(URLContext *h, uint8_t *sig, const uint8_t *digest,
                          int type)
{
    int i;

    for (i = 0; i < 32; i += 8) {
        if (type == 8) {
            /* RTMPE type 8 uses XTEA on the signature */
            rtmpe8_sig(sig + i, sig + i, digest[i] % 15);
        } else if (type == 9) {
            /* RTMPE type 9 uses Blowfish on the signature */
            rtmpe9_sig(sig + i, sig + i, digest[i] % 15);
        }
    }
}