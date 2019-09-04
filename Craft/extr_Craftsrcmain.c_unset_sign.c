#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dirty; int /*<<< orphan*/  signs; } ;
typedef  int /*<<< orphan*/  SignList ;
typedef  TYPE_1__ Chunk ;

/* Variables and functions */
 int chunked (int) ; 
 int /*<<< orphan*/  db_delete_signs (int,int,int) ; 
 TYPE_1__* find_chunk (int,int) ; 
 scalar_t__ sign_list_remove_all (int /*<<< orphan*/ *,int,int,int) ; 

void unset_sign(int x, int y, int z) {
    int p = chunked(x);
    int q = chunked(z);
    Chunk *chunk = find_chunk(p, q);
    if (chunk) {
        SignList *signs = &chunk->signs;
        if (sign_list_remove_all(signs, x, y, z)) {
            chunk->dirty = 1;
            db_delete_signs(x, y, z);
        }
    }
    else {
        db_delete_signs(x, y, z);
    }
}