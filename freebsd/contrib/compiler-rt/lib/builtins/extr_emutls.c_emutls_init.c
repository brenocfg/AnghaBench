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

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int emutls_key_created ; 
 int /*<<< orphan*/  emutls_key_destructor ; 
 int /*<<< orphan*/  emutls_pthread_key ; 
 scalar_t__ pthread_key_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void emutls_init(void) {
  if (pthread_key_create(&emutls_pthread_key, emutls_key_destructor) != 0)
    abort();
  emutls_key_created = true;
}