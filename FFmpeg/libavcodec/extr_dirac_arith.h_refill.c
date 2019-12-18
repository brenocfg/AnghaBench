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
struct TYPE_3__ {int counter; scalar_t__ bytestream; scalar_t__ bytestream_end; int overread; int low; int /*<<< orphan*/  error; } ;
typedef  TYPE_1__ DiracArith ;

/* Variables and functions */
 int /*<<< orphan*/  AVERROR_INVALIDDATA ; 
 int bytestream_get_be16 (scalar_t__*) ; 

__attribute__((used)) static inline void refill(DiracArith *c)
{
    int counter = c->counter;

    if (counter >= 0) {
        int new = bytestream_get_be16(&c->bytestream);

        // the spec defines overread bits to be 1, and streams rely on this
        if (c->bytestream > c->bytestream_end) {
            new |= 0xff;
            if (c->bytestream > c->bytestream_end+1)
                new |= 0xff00;

            c->bytestream = c->bytestream_end;
            c->overread ++;
            if (c->overread > 4)
                c->error = AVERROR_INVALIDDATA;
        }

        c->low += new << counter;
        counter -= 16;
    }
    c->counter = counter;
}