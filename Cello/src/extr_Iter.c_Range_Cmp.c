#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  struct Range* var ;
struct Range {int /*<<< orphan*/  start; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  Range ; 
 struct Range* cast (struct Range*,int /*<<< orphan*/ ) ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int Range_Cmp(var self, var obj) {
  struct Range* r = self;
  struct Range* o = cast(obj, Range);
  return memcmp(&r->start, &o->start, sizeof(int64_t) * 3);
}