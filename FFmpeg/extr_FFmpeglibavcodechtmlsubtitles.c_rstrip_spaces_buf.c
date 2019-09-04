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
struct TYPE_4__ {int len; char* str; } ;
typedef  TYPE_1__ AVBPrint ;

/* Variables and functions */
 scalar_t__ av_bprint_is_complete (TYPE_1__*) ; 

__attribute__((used)) static void rstrip_spaces_buf(AVBPrint *buf)
{
    if (av_bprint_is_complete(buf))
        while (buf->len > 0 && buf->str[buf->len - 1] == ' ')
            buf->str[--buf->len] = 0;
}