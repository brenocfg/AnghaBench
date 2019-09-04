#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int size; TYPE_2__* data; } ;
struct TYPE_7__ {int sign_faces; int /*<<< orphan*/  sign_buffer; TYPE_1__ signs; } ;
struct TYPE_6__ {int /*<<< orphan*/  text; int /*<<< orphan*/  face; int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ SignList ;
typedef  TYPE_2__ Sign ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  TYPE_3__ Chunk ;

/* Variables and functions */
 scalar_t__ _gen_sign_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_faces (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc_faces (int,int) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

void gen_sign_buffer(Chunk *chunk) {
    SignList *signs = &chunk->signs;

    // first pass - count characters
    int max_faces = 0;
    for (int i = 0; i < signs->size; i++) {
        Sign *e = signs->data + i;
        max_faces += strlen(e->text);
    }

    // second pass - generate geometry
    GLfloat *data = malloc_faces(5, max_faces);
    int faces = 0;
    for (int i = 0; i < signs->size; i++) {
        Sign *e = signs->data + i;
        faces += _gen_sign_buffer(
            data + faces * 30, e->x, e->y, e->z, e->face, e->text);
    }

    del_buffer(chunk->sign_buffer);
    chunk->sign_buffer = gen_faces(5, faces, data);
    chunk->sign_faces = faces;
}