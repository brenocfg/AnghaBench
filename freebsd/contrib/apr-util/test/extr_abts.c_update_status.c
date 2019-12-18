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
 int ABTS_STAT_SIZE ; 
 int curr_char ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  quiet ; 
 int* status ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void update_status(void)
{
    if (!quiet) {
        curr_char = (curr_char + 1) % ABTS_STAT_SIZE;
        fprintf(stdout, "\b%c", status[curr_char]);
        fflush(stdout);
    }
}