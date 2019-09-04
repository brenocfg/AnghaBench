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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  total_tftps; int /*<<< orphan*/  total_wgets; int /*<<< orphan*/  total_echoes; int /*<<< orphan*/  total_successes; int /*<<< orphan*/  total_logins; int /*<<< orphan*/  curr_open; int /*<<< orphan*/  total_input; } ;

/* Variables and functions */
 int ATOMIC_GET (int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 TYPE_1__* srv ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void *stats_thread(void *arg)
{
    uint32_t seconds = 0;

    while (TRUE)
    {
#ifndef DEBUG
        printf("%ds\tProcessed: %d\tConns: %d\tLogins: %d\tRan: %d\tEchoes:%d Wgets: %d, TFTPs: %d\n",
               seconds++, ATOMIC_GET(&srv->total_input), ATOMIC_GET(&srv->curr_open), ATOMIC_GET(&srv->total_logins), ATOMIC_GET(&srv->total_successes),
               ATOMIC_GET(&srv->total_echoes), ATOMIC_GET(&srv->total_wgets), ATOMIC_GET(&srv->total_tftps));
#endif
        fflush(stdout);
        sleep(1);
    }
}