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
 int /*<<< orphan*/  pte_osThreadSleep (int) ; 

int
sched_yield (void)
/*
 * ------------------------------------------------------
 * DOCPUBLIC
 *      This function indicates that the calling thread is
 *      willing to give up some time slices to other threads.
 *
 * PARAMETERS
 *      N/A
 *
 *
 * DESCRIPTION
 *      This function indicates that the calling thread is
 *      willing to give up some time slices to other threads.
 *      NOTE: Since this is part of POSIX 1003.1b
 *                (realtime extensions), it is defined as returning
 *                -1 if an error occurs and sets errno to the actual
 *                error.
 *
 * RESULTS
 *              0               successfully created semaphore,
 *              ENOSYS          sched_yield not supported,
 *
 * ------------------------------------------------------
 */
{
  pte_osThreadSleep (1);

  return 0;
}