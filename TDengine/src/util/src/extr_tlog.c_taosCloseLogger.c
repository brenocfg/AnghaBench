#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  asyncThread; int /*<<< orphan*/  buffNotEmpty; } ;

/* Variables and functions */
 TYPE_1__* logHandle ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ taosCheckPthreadValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosStopLog () ; 
 int /*<<< orphan*/  tsem_post (int /*<<< orphan*/ *) ; 

void taosCloseLogger() {
  taosStopLog();
  tsem_post(&(logHandle->buffNotEmpty));
  if (taosCheckPthreadValid(logHandle->asyncThread)) {
    pthread_join(logHandle->asyncThread, NULL);
  }
  // In case that other threads still use log resources causing invalid write in
  // valgrind, we comment two lines below.
  // taosLogBuffDestroy(logHandle);
  // taosCloseLog();
}