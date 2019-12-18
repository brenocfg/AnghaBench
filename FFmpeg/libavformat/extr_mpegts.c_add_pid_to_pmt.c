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
struct Program {int nb_pids; unsigned int* pids; } ;
typedef  int /*<<< orphan*/  MpegTSContext ;

/* Variables and functions */
 int MAX_PIDS_PER_PROGRAM ; 
 struct Program* get_program (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void add_pid_to_pmt(MpegTSContext *ts, unsigned int programid,
                           unsigned int pid)
{
    struct Program *p = get_program(ts, programid);
    int i;
    if (!p)
        return;

    if (p->nb_pids >= MAX_PIDS_PER_PROGRAM)
        return;

    for (i = 0; i < p->nb_pids; i++)
        if (p->pids[i] == pid)
            return;

    p->pids[p->nb_pids++] = pid;
}