#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* str; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  av_bprint_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  avio_feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_line_to_bprint_escaped (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void get_bprint_line(AVIOContext *s, AVBPrint *bp)
{

    do {
        av_bprint_clear(bp);
        read_line_to_bprint_escaped(s, bp);
    } while (!avio_feof(s) && (bp->str[0] == ';' || bp->str[0] == '#' || bp->str[0] == 0));
}