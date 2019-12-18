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
struct Array {int nslots; int nitems; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int Array_Step (struct Array*) ; 
 int /*<<< orphan*/  realloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void Array_Reserve_Less(struct Array* a) {
  if (a->nslots > a->nitems + a->nitems / 2) {
    a->nslots = a->nitems;
    a->data = realloc(a->data, Array_Step(a) * a->nslots);
  }
}