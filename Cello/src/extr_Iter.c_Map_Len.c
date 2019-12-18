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
typedef  struct Map* var ;
struct Map {int /*<<< orphan*/  iter; } ;

/* Variables and functions */
 size_t len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t Map_Len(var self) {
  struct Map* m = self;
  return len(m->iter);
}