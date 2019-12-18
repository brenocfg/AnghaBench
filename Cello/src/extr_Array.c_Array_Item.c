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
typedef  char* var ;
struct Header {int dummy; } ;
struct Array {scalar_t__ data; } ;

/* Variables and functions */
 size_t Array_Step (struct Array*) ; 

__attribute__((used)) static var Array_Item(struct Array* a, size_t i) {
  return (char*)a->data + Array_Step(a) * i + sizeof(struct Header);
}