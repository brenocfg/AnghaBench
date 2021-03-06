#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  gb; } ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ LBRChunk ;
typedef  TYPE_2__ DCALbrDecoder ;

/* Variables and functions */
 scalar_t__ init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_grid_2 (TYPE_2__*,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_lpc (TYPE_2__*,int,int,int,int) ; 
 scalar_t__ parse_ts (TYPE_2__*,int,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_ts1_chunk(DCALbrDecoder *s, LBRChunk *chunk, int ch1, int ch2)
{
    if (!chunk->len)
        return 0;
    if (init_get_bits8(&s->gb, chunk->data, chunk->len) < 0)
        return -1;
    if (parse_lpc(s, ch1, ch2, 2, 3) < 0)
        return -1;
    if (parse_ts(s, ch1, ch2, 2, 4, 0) < 0)
        return -1;
    if (parse_grid_2(s, ch1, ch2, 0, 1, 0) < 0)
        return -1;
    if (parse_ts(s, ch1, ch2, 4, 6, 0) < 0)
        return -1;
    return 0;
}