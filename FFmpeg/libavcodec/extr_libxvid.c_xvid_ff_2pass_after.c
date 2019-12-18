#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int quant; int kblks; int mblks; int ublks; int length; int hlength; } ;
struct TYPE_5__ {int type; TYPE_1__ stats; } ;
typedef  TYPE_2__ xvid_plg_data_t ;
struct xvid_context {char* twopassbuffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_CAT (char*) ; 
 int /*<<< orphan*/  BUFFER_REMAINING (char*) ; 
 int XVID_ERR_FAIL ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char,int,int,int,int,int,int) ; 

__attribute__((used)) static int xvid_ff_2pass_after(struct xvid_context *ref,
                               xvid_plg_data_t *param)
{
    char *log = ref->twopassbuffer;
    const char *frame_types = " ipbs";
    char frame_type;

    /* Quick bounds check */
    if (!log)
        return XVID_ERR_FAIL;

    /* Convert the type given to us into a character */
    if (param->type < 5 && param->type > 0)
        frame_type = frame_types[param->type];
    else
        return XVID_ERR_FAIL;

    snprintf(BUFFER_CAT(log), BUFFER_REMAINING(log),
             "%c %d %d %d %d %d %d\n",
             frame_type, param->stats.quant, param->stats.kblks,
             param->stats.mblks, param->stats.ublks,
             param->stats.length, param->stats.hlength);

    return 0;
}