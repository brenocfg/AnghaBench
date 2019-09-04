#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  error; } ;
typedef  TYPE_1__ LZOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LZO_ERROR ; 
 int INT_MAX ; 
 int get_byte (TYPE_1__*) ; 

__attribute__((used)) static inline int get_len(LZOContext *c, int x, int mask)
{
    int cnt = x & mask;
    if (!cnt) {
        while (!(x = get_byte(c))) {
            if (cnt >= INT_MAX - 1000) {
                c->error |= AV_LZO_ERROR;
                break;
            }
            cnt += 255;
        }
        cnt += mask + x;
    }
    return cnt;
}