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
typedef  int /*<<< orphan*/  esp_partition_t ;
typedef  TYPE_1__* esp_partition_iterator_t ;
struct TYPE_3__ {int /*<<< orphan*/  const* info; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

const esp_partition_t* esp_partition_get(esp_partition_iterator_t iterator)
{
    assert(iterator != NULL);
    return iterator->info;
}