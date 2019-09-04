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
struct TYPE_4__ {int /*<<< orphan*/  table; } ;
struct TYPE_5__ {int* recode; int /*<<< orphan*/  bits; TYPE_1__ vlc; } ;
typedef  TYPE_2__ TM2Codes ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int tm2_get_token(GetBitContext *gb, TM2Codes *code)
{
    int val;
    val = get_vlc2(gb, code->vlc.table, code->bits, 1);
    if(val<0)
        return -1;
    return code->recode[val];
}