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
typedef  int uint64_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  bitbuf_t ;

/* Variables and functions */
 int bits_get (int /*<<< orphan*/ *,int) ; 
 scalar_t__ bits_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int64_t parse_pes_timestamp( bitbuf_t *bb )
{
    int64_t ts;

    ts =  ( (uint64_t)   bits_get(bb,  3) << 30 ) +
                         bits_skip(bb, 1)         +
                       ( bits_get(bb, 15) << 15 ) +
                         bits_skip(bb, 1)         +
                         bits_get(bb, 15);
    bits_skip(bb, 1);
    return ts;
}