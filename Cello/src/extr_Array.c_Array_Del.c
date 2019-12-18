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
typedef  struct Array* var ;
struct Array {size_t nitems; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  Array_Item (struct Array*,size_t) ; 
 int /*<<< orphan*/  destruct (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Array_Del(var self) {
  
  struct Array* a = self;
  
  for(size_t i = 0; i < a->nitems; i++) {
    destruct(Array_Item(a, i));
  }
  
  free(a->data);
  
}