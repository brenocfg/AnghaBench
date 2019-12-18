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

/* Variables and functions */
 uintptr_t atomic_add_fetch_ptr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nextTimerId ; 

__attribute__((used)) static uintptr_t getNextTimerId() {
  uintptr_t id;
  do {
    id = atomic_add_fetch_ptr(&nextTimerId, 1);
  } while (id == 0);
  return id;
}