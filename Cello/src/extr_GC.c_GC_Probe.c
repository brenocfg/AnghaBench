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
typedef  int uint64_t ;
struct GC {scalar_t__ nslots; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */

__attribute__((used)) static uint64_t GC_Probe(struct GC* gc, uint64_t i, uint64_t h) {
  int64_t v = i - (h-1);
  if (v < 0) {
    v = gc->nslots + v;
  }
  return v;
}