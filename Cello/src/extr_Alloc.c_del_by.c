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
typedef  int /*<<< orphan*/  var ;

/* Variables and functions */
#define  ALLOC_RAW 130 
#define  ALLOC_ROOT 129 
#define  ALLOC_STANDARD 128 
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  current (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dealloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destruct (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void del_by(var self, int method) {
  
  switch (method) {
    case ALLOC_STANDARD:
    case ALLOC_ROOT:
#ifndef CELLO_NGC
    rem(current(GC), self);
    return;
#endif
    break;
    case ALLOC_RAW: break;
  }
  
  dealloc(destruct(self));
  
}