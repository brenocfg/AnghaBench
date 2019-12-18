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
typedef  scalar_t__ var ;
struct Array {int dummy; } ;

/* Variables and functions */
 scalar_t__ Array_Item (struct Array*,int /*<<< orphan*/ ) ; 
 int Array_Step (struct Array*) ; 
 scalar_t__ Terminal ; 

__attribute__((used)) static var Array_Iter_Prev(var self, var curr) {
  struct Array* a = self;
  if (curr < Array_Item(a, 0)) {
    return Terminal;
  } else {
    return (char*)curr - Array_Step(a);
  }
}