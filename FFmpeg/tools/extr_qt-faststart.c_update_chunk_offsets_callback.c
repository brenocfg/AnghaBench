#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int depth; } ;
typedef  TYPE_1__ update_chunk_offsets_context_t ;
struct TYPE_11__ {int type; int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ atom_t ;

/* Variables and functions */
#define  CO64_ATOM 134 
#define  MDIA_ATOM 133 
#define  MINF_ATOM 132 
#define  MOOV_ATOM 131 
#define  STBL_ATOM 130 
#define  STCO_ATOM 129 
#define  TRAK_ATOM 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int parse_atoms (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int (*) (void*,TYPE_2__*),TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 int update_co64_offsets (TYPE_1__*,TYPE_2__*) ; 
 int update_stco_offsets (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int update_chunk_offsets_callback(void *ctx, atom_t *atom)
{
    update_chunk_offsets_context_t *context = ctx;
    int ret;

    switch (atom->type) {
    case STCO_ATOM:
        return update_stco_offsets(context, atom);

    case CO64_ATOM:
        return update_co64_offsets(context, atom);

    case MOOV_ATOM:
    case TRAK_ATOM:
    case MDIA_ATOM:
    case MINF_ATOM:
    case STBL_ATOM:
        context->depth++;
        if (context->depth > 10) {
            fprintf(stderr, "atoms too deeply nested\n");
            return -1;
        }

        ret = parse_atoms(
            atom->data,
            atom->size,
            update_chunk_offsets_callback,
            context);
        context->depth--;
        return ret;
    }

    return 0;
}