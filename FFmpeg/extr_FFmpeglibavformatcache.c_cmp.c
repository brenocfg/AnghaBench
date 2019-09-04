#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_2__ {int /*<<< orphan*/  logical_pos; } ;
typedef  TYPE_1__ CacheEntry ;

/* Variables and functions */
 int FFDIFFSIGN (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmp(const void *key, const void *node)
{
    return FFDIFFSIGN(*(const int64_t *)key, ((const CacheEntry *) node)->logical_pos);
}