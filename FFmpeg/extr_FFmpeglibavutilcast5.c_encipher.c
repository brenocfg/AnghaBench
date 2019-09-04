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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int rounds; } ;
typedef  TYPE_1__ AVCAST5 ;

/* Variables and functions */
 int /*<<< orphan*/  AV_RB32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  AV_WB32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  F2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  F3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void encipher(AVCAST5* cs, uint8_t* dst, const uint8_t* src)
{
    uint32_t r, l, f, I;
    l = AV_RB32(src);
    r = AV_RB32(src + 4);
    F1(l, r, 1);
    F2(r, l, 2);
    F3(l, r, 3);
    F1(r, l, 4);
    F2(l, r, 5);
    F3(r, l, 6);
    F1(l, r, 7);
    F2(r, l, 8);
    F3(l, r, 9);
    F1(r, l, 10);
    F2(l, r, 11);
    F3(r, l, 12);
    if (cs->rounds == 16) {
        F1(l, r, 13);
        F2(r, l, 14);
        F3(l, r, 15);
        F1(r, l, 16);
    }
    AV_WB32(dst, r);
    AV_WB32(dst + 4, l);
}