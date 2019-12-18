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
struct TYPE_3__ {int expect; int /*<<< orphan*/  level; int /*<<< orphan*/  inside_chunks; } ;
typedef  TYPE_1__ unpack_user ;

/* Variables and functions */
 int /*<<< orphan*/  SET_LAST_ERROR (char*) ; 
#define  expect_chunks_begin 129 
#define  expect_entry_begin_or_chunks_end 128 
 int expect_key ; 

__attribute__((used)) static inline int unpack_callback_array(unpack_user* u, unsigned int n)
{
    switch(u->expect) {
    case expect_chunks_begin:
        /* b'chunks': [
         *            ^ */
        u->expect = expect_entry_begin_or_chunks_end;
        break;
    case expect_entry_begin_or_chunks_end:
        /* b'chunks': [ (
         *              ^ */
        if(n != 3) {
            SET_LAST_ERROR("Invalid chunk list entry length");
            return -1;
        }
        u->expect = expect_key;
        break;
    default:
        if(u->inside_chunks) {
            SET_LAST_ERROR("Unexpected array start");
            return -1;
        } else {
            u->level++;
            return 0;
        }
    }
    return 0;
}