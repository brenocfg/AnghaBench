#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ref; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_1__ cavs_vector ;

/* Variables and functions */
 int /*<<< orphan*/  MV_BWD_OFFS ; 
 scalar_t__ REF_INTRA ; 
 int abs (scalar_t__) ; 

__attribute__((used)) static inline int get_bs(cavs_vector *mvP, cavs_vector *mvQ, int b)
{
    if ((mvP->ref == REF_INTRA) || (mvQ->ref == REF_INTRA))
        return 2;
    if((abs(mvP->x - mvQ->x) >= 4) ||
       (abs(mvP->y - mvQ->y) >= 4) ||
       (mvP->ref != mvQ->ref))
        return 1;
    if (b) {
        mvP += MV_BWD_OFFS;
        mvQ += MV_BWD_OFFS;
        if((abs(mvP->x - mvQ->x) >= 4) ||
           (abs(mvP->y - mvQ->y) >= 4) ||
           (mvP->ref != mvQ->ref))
            return 1;
    }
    return 0;
}