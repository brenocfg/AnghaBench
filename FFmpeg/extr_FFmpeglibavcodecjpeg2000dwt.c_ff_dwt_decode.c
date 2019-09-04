#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ndeclevels; int type; } ;
typedef  TYPE_1__ DWTContext ;

/* Variables and functions */
#define  FF_DWT53 130 
#define  FF_DWT97 129 
#define  FF_DWT97_INT 128 
 int /*<<< orphan*/  dwt_decode53 (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  dwt_decode97_float (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  dwt_decode97_int (TYPE_1__*,void*) ; 

int ff_dwt_decode(DWTContext *s, void *t)
{
    if (s->ndeclevels == 0)
        return 0;

    switch (s->type) {
    case FF_DWT97:
        dwt_decode97_float(s, t);
        break;
    case FF_DWT97_INT:
        dwt_decode97_int(s, t);
        break;
    case FF_DWT53:
        dwt_decode53(s, t);
        break;
    default:
        return -1;
    }
    return 0;
}