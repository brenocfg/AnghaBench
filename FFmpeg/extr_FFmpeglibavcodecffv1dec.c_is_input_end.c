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
struct TYPE_4__ {scalar_t__ overread; } ;
struct TYPE_5__ {scalar_t__ ac; int /*<<< orphan*/  gb; TYPE_1__ c; } ;
typedef  TYPE_1__ RangeCoder ;
typedef  TYPE_2__ FFV1Context ;

/* Variables and functions */
 scalar_t__ AC_GOLOMB_RICE ; 
 int AVERROR_INVALIDDATA ; 
 scalar_t__ MAX_OVERREAD ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int is_input_end(FFV1Context *s)
{
    if (s->ac != AC_GOLOMB_RICE) {
        RangeCoder *const c = &s->c;
        if (c->overread > MAX_OVERREAD)
            return AVERROR_INVALIDDATA;
    } else {
        if (get_bits_left(&s->gb) < 1)
            return AVERROR_INVALIDDATA;
    }
    return 0;
}