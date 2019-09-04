#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pthread_t ;
typedef  TYPE_1__* locale_t ;
struct TYPE_6__ {struct TYPE_6__* locale; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,TYPE_1__*) ; 
 TYPE_1__* pthread_self () ; 
 int /*<<< orphan*/  puts (char*) ; 

locale_t do_test() {
  pthread_t thread = pthread_self();
  locale_t loc = thread->locale;
  printf("  pthread_self() = %p\n", thread);
  printf("  pthread_self()->locale = %p\n", loc);

  if (!loc) {
    puts("ERROR: loc is null");
  }
  return loc;
}