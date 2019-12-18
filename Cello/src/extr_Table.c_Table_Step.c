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
typedef  int /*<<< orphan*/  uint64_t ;
struct Table {size_t ksize; size_t vsize; } ;
struct Header {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static size_t Table_Step(struct Table* t) {
  return
    sizeof(uint64_t) + 
    sizeof(struct Header) + t->ksize + 
    sizeof(struct Header) + t->vsize;
}