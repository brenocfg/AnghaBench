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
struct Program {int pmt_found; } ;
typedef  int /*<<< orphan*/  MpegTSContext ;

/* Variables and functions */
 struct Program* get_program (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void set_pmt_found(MpegTSContext *ts, unsigned int programid)
{
    struct Program *p = get_program(ts, programid);
    if (!p)
        return;

    p->pmt_found = 1;
}