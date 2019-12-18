#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int genFunc_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* Error ) (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {TYPE_1__* shader; } ;
struct TYPE_6__ {float* sinTable; float* triangleTable; float* squareTable; float* sawToothTable; float* inverseSawToothTable; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_DROP ; 
#define  GF_INVERSE_SAWTOOTH 133 
#define  GF_NONE 132 
#define  GF_SAWTOOTH 131 
#define  GF_SIN 130 
#define  GF_SQUARE 129 
#define  GF_TRIANGLE 128 
 TYPE_4__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 TYPE_3__ tess ; 
 TYPE_2__ tr ; 

__attribute__((used)) static float *TableForFunc( genFunc_t func ) 
{
	switch ( func )
	{
	case GF_SIN:
		return tr.sinTable;
	case GF_TRIANGLE:
		return tr.triangleTable;
	case GF_SQUARE:
		return tr.squareTable;
	case GF_SAWTOOTH:
		return tr.sawToothTable;
	case GF_INVERSE_SAWTOOTH:
		return tr.inverseSawToothTable;
	case GF_NONE:
	default:
		break;
	}

	ri.Error( ERR_DROP, "TableForFunc called with invalid function '%d' in shader '%s'\n", func, tess.shader->name );
	return NULL;
}