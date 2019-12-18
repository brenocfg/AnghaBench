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
struct gomp_thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gomp_tls_key ; 
 struct gomp_thread* pthread_getspecific (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct gomp_thread *gomp_thread (void)
{
  return pthread_getspecific (gomp_tls_key);
}