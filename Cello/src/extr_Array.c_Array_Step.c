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
struct Header {int dummy; } ;
struct Array {size_t tsize; } ;

/* Variables and functions */

__attribute__((used)) static size_t Array_Step(struct Array* a) {
  return a->tsize + sizeof(struct Header);
}