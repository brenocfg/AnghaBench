#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {TYPE_1__ s; } ;
typedef  TYPE_2__ hb_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  HB_BUF_FLAG_EOF ; 
 TYPE_2__* hb_buffer_init (int /*<<< orphan*/ ) ; 

hb_buffer_t * hb_buffer_eof_init(void)
{
    hb_buffer_t * buf = hb_buffer_init(0);
    buf->s.flags = HB_BUF_FLAG_EOF;
    return buf;
}