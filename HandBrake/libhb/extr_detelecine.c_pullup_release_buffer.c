#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pullup_buffer {int /*<<< orphan*/ * lock; } ;

/* Variables and functions */

void pullup_release_buffer( struct pullup_buffer * b,
                            int parity )
{
    if( !b ) return;
    if( (parity+1) & 1 ) b->lock[0]--;
    if( (parity+1) & 2 ) b->lock[1]--;
}