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
typedef  struct Int* var ;
struct Int {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int /*<<< orphan*/  c_int (struct Int*) ; 

__attribute__((used)) static void Int_Assign(var self, var obj) {
  struct Int* i = self;
  i->val = c_int(obj);
}