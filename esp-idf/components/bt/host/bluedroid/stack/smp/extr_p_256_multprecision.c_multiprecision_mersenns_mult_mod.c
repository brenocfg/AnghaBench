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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int KEY_LENGTH_DWORDS_P256 ; 
 int /*<<< orphan*/  multiprecision_fast_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multiprecision_fast_mod_P256 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multiprecision_mult (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void multiprecision_mersenns_mult_mod(DWORD *c, DWORD *a, DWORD *b, uint32_t keyLength)
{
    DWORD cc[2 * KEY_LENGTH_DWORDS_P256];

    multiprecision_mult(cc, a, b, keyLength);
    if (keyLength == 6) {
        multiprecision_fast_mod(c, cc);
    } else if (keyLength == 8) {
        multiprecision_fast_mod_P256(c, cc);
    }
}