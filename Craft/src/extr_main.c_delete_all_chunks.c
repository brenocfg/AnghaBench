#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int chunk_count; TYPE_1__* chunks; } ;
struct TYPE_3__ {int /*<<< orphan*/  sign_buffer; int /*<<< orphan*/  buffer; int /*<<< orphan*/  signs; int /*<<< orphan*/  lights; int /*<<< orphan*/  map; } ;
typedef  TYPE_1__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  del_buffer (int /*<<< orphan*/ ) ; 
 TYPE_2__* g ; 
 int /*<<< orphan*/  map_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sign_list_free (int /*<<< orphan*/ *) ; 

void delete_all_chunks() {
    for (int i = 0; i < g->chunk_count; i++) {
        Chunk *chunk = g->chunks + i;
        map_free(&chunk->map);
        map_free(&chunk->lights);
        sign_list_free(&chunk->signs);
        del_buffer(chunk->buffer);
        del_buffer(chunk->sign_buffer);
    }
    g->chunk_count = 0;
}