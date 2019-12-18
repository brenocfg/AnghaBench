#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int16_t ;
struct TYPE_18__ {TYPE_4__* progress; } ;
struct TYPE_19__ {TYPE_5__ tf; } ;
struct TYPE_22__ {int picture_structure; TYPE_6__ cur_pic; } ;
struct TYPE_21__ {int reference; TYPE_3__* parent; } ;
struct TYPE_20__ {int mb_y; int** ref_cache; TYPE_8__** ref_list; } ;
struct TYPE_17__ {scalar_t__ data; } ;
struct TYPE_15__ {TYPE_1__* progress; } ;
struct TYPE_16__ {TYPE_2__ tf; } ;
struct TYPE_14__ {scalar_t__ data; } ;
typedef  TYPE_7__ H264SliceContext ;
typedef  TYPE_8__ H264Ref ;
typedef  TYPE_9__ H264Context ;

/* Variables and functions */
 scalar_t__ FFMAX (scalar_t__,int) ; 
 int MB_FIELD (TYPE_7__*) ; 
 int get_lowest_part_list_y (TYPE_7__*,int,int,int,int) ; 
 size_t* scan8 ; 

__attribute__((used)) static inline void get_lowest_part_y(const H264Context *h, H264SliceContext *sl,
                                     int16_t refs[2][48], int n,
                                     int height, int y_offset, int list0,
                                     int list1, int *nrefs)
{
    int my;

    y_offset += 16 * (sl->mb_y >> MB_FIELD(sl));

    if (list0) {
        int ref_n = sl->ref_cache[0][scan8[n]];
        H264Ref *ref = &sl->ref_list[0][ref_n];

        // Error resilience puts the current picture in the ref list.
        // Don't try to wait on these as it will cause a deadlock.
        // Fields can wait on each other, though.
        if (ref->parent->tf.progress->data != h->cur_pic.tf.progress->data ||
            (ref->reference & 3) != h->picture_structure) {
            my = get_lowest_part_list_y(sl, n, height, y_offset, 0);
            if (refs[0][ref_n] < 0)
                nrefs[0] += 1;
            refs[0][ref_n] = FFMAX(refs[0][ref_n], my);
        }
    }

    if (list1) {
        int ref_n    = sl->ref_cache[1][scan8[n]];
        H264Ref *ref = &sl->ref_list[1][ref_n];

        if (ref->parent->tf.progress->data != h->cur_pic.tf.progress->data ||
            (ref->reference & 3) != h->picture_structure) {
            my = get_lowest_part_list_y(sl, n, height, y_offset, 1);
            if (refs[1][ref_n] < 0)
                nrefs[1] += 1;
            refs[1][ref_n] = FFMAX(refs[1][ref_n], my);
        }
    }
}