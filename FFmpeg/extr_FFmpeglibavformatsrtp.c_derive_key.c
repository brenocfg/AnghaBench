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
struct AVAES {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  encrypt_counter (struct AVAES*,int*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void derive_key(struct AVAES *aes, const uint8_t *salt, int label,
                       uint8_t *out, int outlen)
{
    uint8_t input[16] = { 0 };
    memcpy(input, salt, 14);
    // Key derivation rate assumed to be zero
    input[14 - 7] ^= label;
    memset(out, 0, outlen);
    encrypt_counter(aes, input, out, outlen);
}