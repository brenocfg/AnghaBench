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
 int /*<<< orphan*/  db_insert_sign (int,int,int,int,int,int,char const*) ; 
 TYPE_1__* find_chunk (int,int) ; 
 int /*<<< orphan*/  sign_list_add (int /*<<< orphan*/ *,int,int,int,int,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  unset_sign_face (int,int,int,int) ; 

void _set_sign(
    int p, int q, int x, int y, int z, int face, const char *text, int dirty)
{
    if (strlen(text) == 0) {
        unset_sign_face(x, y, z, face);
        return;
    }
    Chunk *chunk = find_chunk(p, q);
    if (chunk) {
        SignList *signs = &chunk->signs;
        sign_list_add(signs, x, y, z, face, text);
        if (dirty) {
            chunk->dirty = 1;
        }
    }
    db_insert_sign(p, q, x, y, z, face, text);
}