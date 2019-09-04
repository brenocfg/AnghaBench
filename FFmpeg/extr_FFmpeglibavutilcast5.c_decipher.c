#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int rounds; } ;
typedef  TYPE_1__ AVCAST5 ;

/* Variables and functions */
 int /*<<< orphan*/  AV_RB32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  AV_WB32 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  F2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  F3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void decipher(AVCAST5* cs, uint8_t* dst, const uint8_t* src, uint8_t *iv)
{
    uint32_t f, I, r, l;
    l = AV_RB32(src);
    r = AV_RB32(src + 4);
    if (cs->rounds == 16) {
        F1(l, r, 16);
        F3(r, l, 15);
        F2(l, r, 14);
        F1(r, l, 13);
    }
    F3(l, r, 12);
    F2(r, l, 11);
    F1(l, r, 10);
    F3(r, l, 9);
    F2(l, r, 8);
    F1(r, l, 7);
    F3(l, r, 6);
    F2(r, l, 5);
    F1(l, r, 4);
    F3(r, l, 3);
    F2(l, r, 2);
    F1(r, l, 1);
    if (iv) {
        r ^= AV_RB32(iv);
        l ^= AV_RB32(iv + 4);
        memcpy(iv, src, 8);
    }
    AV_WB32(dst, r);
    AV_WB32(dst + 4, l);
}