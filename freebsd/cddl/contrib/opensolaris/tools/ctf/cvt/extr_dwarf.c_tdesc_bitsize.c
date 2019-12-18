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
struct TYPE_5__ {int t_type; size_t t_size; int /*<<< orphan*/  t_id; struct TYPE_5__* t_tdesc; TYPE_1__* t_intr; } ;
typedef  TYPE_2__ tdesc_t ;
struct TYPE_4__ {size_t intr_nbits; } ;

/* Variables and functions */
#define  ARRAY 139 
#define  CONST 138 
#define  ENUM 137 
#define  FORWARD 136 
#define  FUNCTION 135 
#define  INTRINSIC 134 
 size_t NBBY ; 
#define  POINTER 133 
#define  RESTRICT 132 
#define  STRUCT 131 
#define  TYPEDEF 130 
#define  UNION 129 
#define  VOLATILE 128 
 int /*<<< orphan*/  terminate (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static size_t
tdesc_bitsize(tdesc_t *tdp)
{
	for (;;) {
		switch (tdp->t_type) {
		case INTRINSIC:
			return (tdp->t_intr->intr_nbits);

		case ARRAY:
		case FUNCTION:
		case STRUCT:
		case UNION:
		case ENUM:
		case POINTER:
			return (tdp->t_size * NBBY);

		case FORWARD:
			return (0);

		case TYPEDEF:
		case VOLATILE:
		case RESTRICT:
		case CONST:
			tdp = tdp->t_tdesc;
			continue;

		case 0: /* not yet defined */
			return (0);

		default:
			terminate("tdp %u: tdesc_bitsize on unknown type %d\n",
			    tdp->t_id, tdp->t_type);
		}
	}
}