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
struct TYPE_5__ {scalar_t__ magic; int /*<<< orphan*/  p_file; } ;
typedef  TYPE_1__ mpc_reader_stdio ;
struct TYPE_6__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ mpc_reader ;

/* Variables and functions */
 scalar_t__ STDIO_MAGIC ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void
mpc_reader_exit_stdio(mpc_reader *p_reader)
{
    mpc_reader_stdio *p_stdio = (mpc_reader_stdio*) p_reader->data;
    if(p_stdio->magic != STDIO_MAGIC) return;
    fclose(p_stdio->p_file);
    free(p_stdio);
    p_reader->data = NULL;
}