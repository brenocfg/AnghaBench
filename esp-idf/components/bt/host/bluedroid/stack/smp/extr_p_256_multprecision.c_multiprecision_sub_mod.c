#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {scalar_t__* p; } ;
struct TYPE_3__ {scalar_t__* p; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_LENGTH_DWORDS_P192 ; 
 int /*<<< orphan*/  KEY_LENGTH_DWORDS_P256 ; 
 TYPE_2__ curve ; 
 TYPE_1__ curve_p256 ; 
 int /*<<< orphan*/  multiprecision_add (scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ multiprecision_sub (scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 

void multiprecision_sub_mod(DWORD *c, DWORD *a, DWORD *b, uint32_t keyLength)
{
    DWORD borrow;
    DWORD *modp;

    if (keyLength == KEY_LENGTH_DWORDS_P192) {
        modp = curve.p;
    } else if (keyLength == KEY_LENGTH_DWORDS_P256) {
        modp = curve_p256.p;
    } else {
        return;
    }

    borrow = multiprecision_sub(c, a, b, keyLength);
    if (borrow) {
        multiprecision_add(c, c, modp, keyLength);
    }
}