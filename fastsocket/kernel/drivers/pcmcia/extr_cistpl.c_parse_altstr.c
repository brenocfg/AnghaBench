#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {int TupleDataLen; scalar_t__ TupleData; } ;
typedef  TYPE_1__ tuple_t ;
struct TYPE_6__ {int /*<<< orphan*/  ns; int /*<<< orphan*/  ofs; int /*<<< orphan*/  str; } ;
typedef  TYPE_2__ cistpl_altstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CISTPL_MAX_ALTSTR_STRINGS ; 
 int parse_strings (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_altstr(tuple_t *tuple, cistpl_altstr_t *altstr)
{
    u_char *p, *q;
    
    p = (u_char *)tuple->TupleData;
    q = p + tuple->TupleDataLen;
    
    return parse_strings(p, q, CISTPL_MAX_ALTSTR_STRINGS,
			 altstr->str, altstr->ofs, &altstr->ns);
}