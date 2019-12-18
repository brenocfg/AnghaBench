#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int alloc; int size; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ hb_tx3g_output_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_error (char*) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int check_realloc_output(hb_tx3g_output_buf_t * output, int size)
{
    if (output->alloc < size)
    {
        uint8_t * tmp;

        output->alloc = size + 1024;
        output->size  = size;
        tmp = realloc(output->buf, output->alloc);
        if (tmp == NULL)
        {
            hb_error("realloc failed!");
            free(output->buf);
            output->size = 0;
            output->alloc = 0;
            output->buf   = NULL;
            return 0;
        }
        output->buf = tmp;
    }
    return 1;
}