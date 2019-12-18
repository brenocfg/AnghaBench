#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/  buffMutex; int /*<<< orphan*/  buffNotEmpty; } ;
typedef  TYPE_1__ SLogBuff ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tfree (TYPE_1__*) ; 
 int /*<<< orphan*/  tsem_destroy (int /*<<< orphan*/ *) ; 

void taosLogBuffDestroy(SLogBuff *tLogBuff) {
  tsem_destroy(&(tLogBuff->buffNotEmpty));
  pthread_mutex_destroy(&(tLogBuff->buffMutex));
  free(tLogBuff->buffer);
  tfree(tLogBuff);
}