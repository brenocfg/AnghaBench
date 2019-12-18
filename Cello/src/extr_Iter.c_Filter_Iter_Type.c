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
typedef  struct Filter* var ;
struct Filter {int /*<<< orphan*/  iter; } ;

/* Variables and functions */
 struct Filter* iter_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static var Filter_Iter_Type(var self) {
  struct Filter* f = self;
  return iter_type(f->iter);
}