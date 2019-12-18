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
typedef  scalar_t__ u_int ;
struct TYPE_3__ {scalar_t__ TupleLink; scalar_t__ TupleOffset; scalar_t__ TupleDataLen; scalar_t__ CISOffset; int /*<<< orphan*/  TupleData; int /*<<< orphan*/  TupleDataMax; int /*<<< orphan*/  Flags; } ;
typedef  TYPE_1__ tuple_t ;
struct pcmcia_socket {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 int /*<<< orphan*/  SPACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_cis_cache (struct pcmcia_socket*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pccard_get_tuple_data(struct pcmcia_socket *s, tuple_t *tuple)
{
    u_int len;

    if (!s)
	return -EINVAL;

    if (tuple->TupleLink < tuple->TupleOffset)
	return -ENOSPC;
    len = tuple->TupleLink - tuple->TupleOffset;
    tuple->TupleDataLen = tuple->TupleLink;
    if (len == 0)
	return 0;
    read_cis_cache(s, SPACE(tuple->Flags),
		   tuple->CISOffset + tuple->TupleOffset,
		   _MIN(len, tuple->TupleDataMax), tuple->TupleData);
    return 0;
}