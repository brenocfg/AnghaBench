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
typedef  int uint32_t ;
struct TYPE_3__ {int flags; } ;
typedef  int /*<<< orphan*/  MOVTrack ;
typedef  TYPE_1__ MOVIentry ;

/* Variables and functions */
 int MOV_FRAG_SAMPLE_FLAG_DEPENDS_NO ; 
 int MOV_FRAG_SAMPLE_FLAG_DEPENDS_YES ; 
 int MOV_FRAG_SAMPLE_FLAG_IS_NON_SYNC ; 
 int MOV_SYNC_SAMPLE ; 

__attribute__((used)) static uint32_t get_sample_flags(MOVTrack *track, MOVIentry *entry)
{
    return entry->flags & MOV_SYNC_SAMPLE ? MOV_FRAG_SAMPLE_FLAG_DEPENDS_NO :
           (MOV_FRAG_SAMPLE_FLAG_DEPENDS_YES | MOV_FRAG_SAMPLE_FLAG_IS_NON_SYNC);
}