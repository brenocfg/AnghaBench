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
typedef  struct Mutex* var ;
struct Mutex {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  CreateMutex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Mutex_New(var self, var args) {
  struct Mutex* m = self;
#if defined(CELLO_UNIX)
  pthread_mutex_init(&m->mutex, NULL);
#elif defined(CELLO_WINDOWS)
  m->mutex = CreateMutex(NULL, false, NULL);
#endif
}