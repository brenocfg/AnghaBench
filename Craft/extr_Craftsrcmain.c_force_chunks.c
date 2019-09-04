#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ chunk_count; TYPE_3__* chunks; } ;
struct TYPE_11__ {scalar_t__ dirty; } ;
struct TYPE_9__ {int /*<<< orphan*/  z; int /*<<< orphan*/  x; } ;
struct TYPE_10__ {TYPE_1__ state; } ;
typedef  TYPE_1__ State ;
typedef  TYPE_2__ Player ;
typedef  TYPE_3__ Chunk ;

/* Variables and functions */
 scalar_t__ MAX_CHUNKS ; 
 int chunked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_chunk (TYPE_3__*,int,int) ; 
 TYPE_3__* find_chunk (int,int) ; 
 TYPE_5__* g ; 
 int /*<<< orphan*/  gen_chunk_buffer (TYPE_3__*) ; 

void force_chunks(Player *player) {
    State *s = &player->state;
    int p = chunked(s->x);
    int q = chunked(s->z);
    int r = 1;
    for (int dp = -r; dp <= r; dp++) {
        for (int dq = -r; dq <= r; dq++) {
            int a = p + dp;
            int b = q + dq;
            Chunk *chunk = find_chunk(a, b);
            if (chunk) {
                if (chunk->dirty) {
                    gen_chunk_buffer(chunk);
                }
            }
            else if (g->chunk_count < MAX_CHUNKS) {
                chunk = g->chunks + g->chunk_count++;
                create_chunk(chunk, a, b);
                gen_chunk_buffer(chunk);
            }
        }
    }
}