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
struct TYPE_3__ {scalar_t__ output_bytes; int /*<<< orphan*/  pb; } ;
typedef  TYPE_1__ LZWEncodeState ;

/* Variables and functions */
 int put_bits_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int writtenBytes(LZWEncodeState *s){
    int ret = put_bits_count(&s->pb) >> 3;
    ret -= s->output_bytes;
    s->output_bytes += ret;
    return ret;
}