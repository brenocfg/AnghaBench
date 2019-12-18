#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct segment_command_64 {int dummy; } ;
struct segment_command {int dummy; } ;
typedef  scalar_t__ boolean_t ;
struct TYPE_5__ {int nitems; } ;
struct TYPE_6__ {TYPE_1__ sects; } ;
typedef  TYPE_2__ KXLDSeg ;

/* Variables and functions */
 int /*<<< orphan*/  check (TYPE_2__ const*) ; 
 int kxld_sect_get_macho_header_size (scalar_t__) ; 

u_long
kxld_seg_get_macho_header_size(const KXLDSeg *seg, boolean_t is_32_bit)
{
    u_long size = 0;
    
    check(seg);

    if (is_32_bit) {
        size += sizeof(struct segment_command);
    } else {
        size += sizeof(struct segment_command_64);
    }
    size += seg->sects.nitems * kxld_sect_get_macho_header_size(is_32_bit);

    return size;
}