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
 int /*<<< orphan*/  dmadone ; 
 int framecount ; 
 scalar_t__ lastup ; 
 int /*<<< orphan*/  printf (char*,int,scalar_t__,float) ; 
 int /*<<< orphan*/  pvr_scene_finish () ; 
 int /*<<< orphan*/  sem_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_wait (int /*<<< orphan*/ *) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void VIDDCVdp2DrawEnd(void)  {
    /* Make sure we don't have any texture dma still going on... */
    sem_wait(&dmadone);
    sem_signal(&dmadone);

    pvr_scene_finish();

    ++framecount;

    if(lastup + 10 <= time(NULL))    {
        printf("%d frames in %d seconds FPS: %f\n", framecount, time(NULL) -
               lastup, ((float)(framecount)) / (time(NULL) - lastup));
        framecount = 0;
        lastup = time(NULL);
    }
}