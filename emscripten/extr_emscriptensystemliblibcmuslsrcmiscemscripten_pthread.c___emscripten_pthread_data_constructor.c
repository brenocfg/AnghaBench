#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  global_locale; } ;
struct TYPE_3__ {int /*<<< orphan*/ * locale; } ;

/* Variables and functions */
 TYPE_2__ libc ; 
 TYPE_1__* pthread_self () ; 

__attribute__((constructor))
void __emscripten_pthread_data_constructor(void) {
    pthread_self()->locale = &libc.global_locale;
}