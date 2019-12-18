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
struct TYPE_4__ {int t_type; struct TYPE_4__* t_tdesc; } ;
typedef  TYPE_1__ tdesc_t ;

/* Variables and functions */
#define  CONST 131 
#define  RESTRICT 130 
#define  TYPEDEF 129 
#define  VOLATILE 128 

__attribute__((used)) static tdesc_t *
tdesc_basetype(tdesc_t *tdp)
{
	for (;;) {
		switch (tdp->t_type) {
		case TYPEDEF:
		case VOLATILE:
		case RESTRICT:
		case CONST:
			tdp = tdp->t_tdesc;
			break;
		case 0: /* not yet defined */
			return (NULL);
		default:
			return (tdp);
		}
	}
}