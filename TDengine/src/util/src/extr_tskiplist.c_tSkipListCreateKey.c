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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ tSkipListKey ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  tVariantCreateFromBinary (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tSkipListKey tSkipListCreateKey(int32_t type, char *val, size_t keyLength) {
  tSkipListKey k = {0};
  tVariantCreateFromBinary(&k, val, (uint32_t) keyLength, (uint32_t) type);
  return k;
}