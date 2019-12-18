#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* avf; int /*<<< orphan*/  current_segment_final_filename_fmt; } ;
typedef  TYPE_2__ VariantStream ;
struct TYPE_9__ {int flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  url; } ;
typedef  TYPE_3__ HLSContext ;

/* Variables and functions */
 int HLS_SECOND_LEVEL_SEGMENT_DURATION ; 
 int HLS_SECOND_LEVEL_SEGMENT_SIZE ; 
 int /*<<< orphan*/  ff_rename (char*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sls_flag_file_rename(HLSContext *hls, VariantStream *vs, char *old_filename) {
    if ((hls->flags & (HLS_SECOND_LEVEL_SEGMENT_SIZE | HLS_SECOND_LEVEL_SEGMENT_DURATION)) &&
        strlen(vs->current_segment_final_filename_fmt)) {
        ff_rename(old_filename, vs->avf->url, hls);
    }
}