#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_4__ {int /*<<< orphan*/  sects; } ;
typedef  TYPE_1__ KXLDSeg ;
typedef  int /*<<< orphan*/  KXLDSect ;

/* Variables and functions */
 int /*<<< orphan*/  check (TYPE_1__ const*) ; 
 scalar_t__ kxld_array_get_item (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static KXLDSect * 
get_sect_by_index(const KXLDSeg *seg, u_int idx)
{
    check(seg);

    return *(KXLDSect **) kxld_array_get_item(&seg->sects, idx);
}