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
typedef  struct Thread* var ;
struct Thread {int /*<<< orphan*/  tls; } ;

/* Variables and functions */
 int /*<<< orphan*/  rem (int /*<<< orphan*/ ,struct Thread*) ; 

__attribute__((used)) static void Thread_Rem(var self, var key) {
  struct Thread* t = self;
  rem(t->tls, key);
}