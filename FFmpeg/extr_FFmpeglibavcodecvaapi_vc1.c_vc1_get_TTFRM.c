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
struct TYPE_3__ {int ttfrm; } ;
typedef  TYPE_1__ VC1Context ;

/* Variables and functions */
#define  TT_4X4 131 
#define  TT_4X8 130 
#define  TT_8X4 129 
#define  TT_8X8 128 

__attribute__((used)) static inline int vc1_get_TTFRM(const VC1Context *v)
{
    switch (v->ttfrm) {
    case TT_8X8: return 0;
    case TT_8X4: return 1;
    case TT_4X8: return 2;
    case TT_4X4: return 3;
    }
    return 0;
}