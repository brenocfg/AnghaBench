#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  gb; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ LBRChunk ;
typedef  TYPE_2__ DCALbrDecoder ;

/* Variables and functions */
 scalar_t__ init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int parse_tonal (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_tonal_group(DCALbrDecoder *s, LBRChunk *chunk)
{
    if (!chunk->len)
        return 0;

    if (init_get_bits8(&s->gb, chunk->data, chunk->len) < 0)
        return -1;

    return parse_tonal(s, chunk->id);
}