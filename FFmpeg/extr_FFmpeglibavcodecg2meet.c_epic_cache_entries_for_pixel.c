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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * list; } ;
typedef  TYPE_1__ ePICPixHashElem ;
typedef  int /*<<< orphan*/  ePICPixHash ;

/* Variables and functions */
 TYPE_1__* epic_hash_find (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int epic_cache_entries_for_pixel(const ePICPixHash *hash,
                                               uint32_t pix)
{
    ePICPixHashElem *hash_elem = epic_hash_find(hash, pix);

    if (hash_elem != NULL && hash_elem->list != NULL)
        return 1;

    return 0;
}