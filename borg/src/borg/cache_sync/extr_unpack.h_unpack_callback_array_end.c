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
struct TYPE_6__ {int size; int csize; int /*<<< orphan*/  key; } ;
struct TYPE_5__ {int size; int csize; } ;
struct TYPE_7__ {int expect; int /*<<< orphan*/  level; int /*<<< orphan*/  inside_chunks; TYPE_2__ current; TYPE_1__ item; int /*<<< orphan*/  chunks; } ;
typedef  TYPE_3__ unpack_user ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int MIN (int,int) ; 
 int /*<<< orphan*/  SET_LAST_ERROR (char*) ; 
 int _MAX_VALUE ; 
 int /*<<< orphan*/  _htole32 (int) ; 
 int _le32toh (int /*<<< orphan*/ ) ; 
#define  expect_entry_begin_or_chunks_end 129 
#define  expect_entry_end 128 
 int expect_map_item_end ; 
 scalar_t__ hashindex_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashindex_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int unpack_callback_array_end(unpack_user* u)
{
    uint32_t *cache_entry;
    uint32_t cache_values[3];
    uint64_t refcount;

    switch(u->expect) {
    case expect_entry_end:
        /* b'chunks': [ ( b'1234...', 123, 345 )
         *                                     ^ */
        cache_entry = (uint32_t*) hashindex_get(u->chunks, u->current.key);
        if(cache_entry) {
            refcount = _le32toh(cache_entry[0]);
            if(refcount > _MAX_VALUE) {
                SET_LAST_ERROR("invalid reference count");
                return -1;
            }
            refcount += 1;
            cache_entry[0] = _htole32(MIN(refcount, _MAX_VALUE));
        } else {
            /* refcount, size, csize */
            cache_values[0] = _htole32(1);
            cache_values[1] = _htole32(u->current.size);
            cache_values[2] = _htole32(u->current.csize);
            if(!hashindex_set(u->chunks, u->current.key, cache_values)) {
                SET_LAST_ERROR("hashindex_set failed");
                return -1;
            }
        }
        u->item.size += u->current.size;
        u->item.csize += u->current.csize;

        u->expect = expect_entry_begin_or_chunks_end;
        break;
    case expect_entry_begin_or_chunks_end:
        /* b'chunks': [ ]
         *              ^ */
        /* end of Item.chunks */
        u->inside_chunks = 0;
        u->expect = expect_map_item_end;
        break;
    default:
        if(u->inside_chunks) {
            SET_LAST_ERROR("Invalid state transition (unexpected array end)");
            return -1;
        } else {
            u->level--;
            return 0;
        }
    }
    return 0;
}