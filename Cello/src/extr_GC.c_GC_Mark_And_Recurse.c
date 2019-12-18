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
struct GC {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GC_Mark_Item (struct GC*,void*) ; 
 int /*<<< orphan*/  GC_Recurse (struct GC*,void*) ; 

__attribute__((used)) static void GC_Mark_And_Recurse(struct GC* gc, void* ptr) {
  GC_Mark_Item(gc, ptr);
  GC_Recurse(gc, ptr);
}