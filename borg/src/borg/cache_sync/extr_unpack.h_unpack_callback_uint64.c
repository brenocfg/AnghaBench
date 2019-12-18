#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* csize; void* size; } ;
struct TYPE_5__ {int expect; TYPE_1__ current; } ;
typedef  TYPE_2__ unpack_user ;
typedef  void* int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNEXPECTED (char*) ; 
#define  expect_csize 129 
 int expect_entry_end ; 
#define  expect_size 128 

__attribute__((used)) static inline int unpack_callback_uint64(unpack_user* u, int64_t d)
{
    switch(u->expect) {
        case expect_size:
            u->current.size = d;
            u->expect = expect_csize;
            break;
        case expect_csize:
            u->current.csize = d;
            u->expect = expect_entry_end;
            break;
        default:
            UNEXPECTED("integer");
    }
    return 0;
}