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
typedef  TYPE_1__* shared_bitmap_info_t ;
typedef  int /*<<< orphan*/  hashval_t ;
struct TYPE_2__ {int /*<<< orphan*/  hashcode; } ;

/* Variables and functions */

__attribute__((used)) static hashval_t
shared_bitmap_hash (const void *p)
{
  const shared_bitmap_info_t bi = (shared_bitmap_info_t) p;
  return bi->hashcode;
}