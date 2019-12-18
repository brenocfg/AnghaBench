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
struct TYPE_3__ {int t_type; size_t t_size; int /*<<< orphan*/  t_id; struct TYPE_3__* t_tdesc; } ;
typedef  TYPE_1__ tdesc_t ;

/* Variables and functions */
#define  ARRAY 139 
#define  CONST 138 
#define  ENUM 137 
#define  FORWARD 136 
#define  FUNCTION 135 
#define  INTRINSIC 134 
#define  POINTER 133 
#define  RESTRICT 132 
#define  STRUCT 131 
#define  TYPEDEF 130 
#define  UNION 129 
#define  VOLATILE 128 
 int /*<<< orphan*/  terminate (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static size_t
tdesc_size(tdesc_t *tdp)
{
	for (;;) {
		switch (tdp->t_type) {
		case INTRINSIC:
		case POINTER:
		case ARRAY:
		case FUNCTION:
		case STRUCT:
		case UNION:
		case ENUM:
			return (tdp->t_size);

		case FORWARD:
			return (0);

		case TYPEDEF:
		case VOLATILE:
		case CONST:
		case RESTRICT:
			tdp = tdp->t_tdesc;
			continue;

		case 0: /* not yet defined */
			return (0);

		default:
			terminate("tdp %u: tdesc_size on unknown type %d\n",
			    tdp->t_id, tdp->t_type);
		}
	}
}