#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* finder_lines; } ;
typedef  TYPE_2__ qr_reader ;
struct TYPE_5__ {TYPE_2__* lines; int /*<<< orphan*/  clines; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  zprintf (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void _zbar_qr_destroy (qr_reader *reader)
{
    zprintf(1, "max finder lines = %dx%d\n",
            reader->finder_lines[0].clines,
            reader->finder_lines[1].clines);
    if(reader->finder_lines[0].lines)
        free(reader->finder_lines[0].lines);
    if(reader->finder_lines[1].lines)
        free(reader->finder_lines[1].lines);
    free(reader);
}