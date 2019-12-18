#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* Read ) (TYPE_2__*,void*,size_t*) ;} ;
struct TYPE_3__ {size_t size; size_t pos; size_t buf; TYPE_2__* realStream; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ CLookToRead ;

/* Variables and functions */
 int /*<<< orphan*/  SZ_OK ; 
 int /*<<< orphan*/  memcpy (void*,size_t,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,void*,size_t*) ; 

__attribute__((used)) static SRes LookToRead_Read(void *pp, void *buf, size_t *size)
{
   CLookToRead *p = (CLookToRead *)pp;
   size_t rem = p->size - p->pos;
   if (rem == 0)
      return p->realStream->Read(p->realStream, buf, size);
   if (rem > *size)
      rem = *size;
   memcpy(buf, p->buf + p->pos, rem);
   p->pos += rem;
   *size = rem;
   return SZ_OK;
}