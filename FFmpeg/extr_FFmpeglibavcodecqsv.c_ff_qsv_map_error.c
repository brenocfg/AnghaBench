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
typedef  scalar_t__ mfxStatus ;
struct TYPE_3__ {scalar_t__ mfxerr; char* desc; int averr; } ;

/* Variables and functions */
 int AVERROR_UNKNOWN ; 
 int FF_ARRAY_ELEMS (TYPE_1__*) ; 
 TYPE_1__* qsv_errors ; 

int ff_qsv_map_error(mfxStatus mfx_err, const char **desc)
{
    int i;
    for (i = 0; i < FF_ARRAY_ELEMS(qsv_errors); i++) {
        if (qsv_errors[i].mfxerr == mfx_err) {
            if (desc)
                *desc = qsv_errors[i].desc;
            return qsv_errors[i].averr;
        }
    }
    if (desc)
        *desc = "unknown error";
    return AVERROR_UNKNOWN;
}