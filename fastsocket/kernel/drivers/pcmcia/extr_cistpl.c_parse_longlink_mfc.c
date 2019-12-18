#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_char ;
struct TYPE_7__ {int TupleDataLen; scalar_t__ TupleData; } ;
typedef  TYPE_2__ tuple_t ;
struct TYPE_8__ {int nfn; TYPE_1__* fn; } ;
typedef  TYPE_3__ cistpl_longlink_mfc_t ;
struct TYPE_6__ {int /*<<< orphan*/  addr; void* space; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  get_unaligned_le32 (void**) ; 

__attribute__((used)) static int parse_longlink_mfc(tuple_t *tuple,
			      cistpl_longlink_mfc_t *link)
{
    u_char *p;
    int i;
    
    p = (u_char *)tuple->TupleData;
    
    link->nfn = *p; p++;
    if (tuple->TupleDataLen <= link->nfn*5)
	return -EINVAL;
    for (i = 0; i < link->nfn; i++) {
	link->fn[i].space = *p; p++;
	link->fn[i].addr = get_unaligned_le32(p);
	p += 4;
    }
    return 0;
}