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
struct TYPE_3__ {scalar_t__ stack_ptr; char* stack; } ;
typedef  TYPE_1__ WebVTTContext ;

/* Variables and functions */
 scalar_t__ WEBVTT_STACK_SIZE ; 

__attribute__((used)) static int webvtt_stack_push(WebVTTContext *s, const char c)
{
    if (s->stack_ptr >= WEBVTT_STACK_SIZE)
        return -1;
    s->stack[s->stack_ptr++] = c;
    return 0;
}