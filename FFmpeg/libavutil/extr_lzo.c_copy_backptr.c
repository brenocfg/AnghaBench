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
struct TYPE_3__ {int /*<<< orphan*/ * out; int /*<<< orphan*/  error; int /*<<< orphan*/ * out_end; int /*<<< orphan*/ * out_start; } ;
typedef  TYPE_1__ LZOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LZO_INVALID_BACKPTR ; 
 int /*<<< orphan*/  AV_LZO_OUTPUT_FULL ; 
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_memcpy_backptr (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline void copy_backptr(LZOContext *c, int back, int cnt)
{
    register uint8_t *dst       = c->out;
    av_assert0(cnt > 0);
    if (dst - c->out_start < back) {
        c->error |= AV_LZO_INVALID_BACKPTR;
        return;
    }
    if (cnt > c->out_end - dst) {
        cnt       = FFMAX(c->out_end - dst, 0);
        c->error |= AV_LZO_OUTPUT_FULL;
    }
    av_memcpy_backptr(dst, back, cnt);
    c->out = dst + cnt;
}