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
struct TYPE_6__ {int /*<<< orphan*/  data; int /*<<< orphan*/  faces; int /*<<< orphan*/  maxy; int /*<<< orphan*/  miny; } ;
typedef  TYPE_1__ WorkerItem ;
struct TYPE_7__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/  faces; int /*<<< orphan*/  maxy; int /*<<< orphan*/  miny; } ;
typedef  TYPE_2__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  del_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_faces (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sign_buffer (TYPE_2__*) ; 

void generate_chunk(Chunk *chunk, WorkerItem *item) {
    chunk->miny = item->miny;
    chunk->maxy = item->maxy;
    chunk->faces = item->faces;
    del_buffer(chunk->buffer);
    chunk->buffer = gen_faces(10, item->faces, item->data);
    gen_sign_buffer(chunk);
}