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
struct spu_link_hash_table {TYPE_2__* stub; } ;
typedef  int bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_5__ {int flags; scalar_t__ size; TYPE_1__* output_section; } ;
typedef  TYPE_2__ asection ;
struct TYPE_4__ {int /*<<< orphan*/ * owner; } ;

/* Variables and functions */
 int SEC_ALLOC ; 
 int SEC_CODE ; 
 int SEC_LOAD ; 

__attribute__((used)) static bfd_boolean
interesting_section (asection *s, bfd *obfd, struct spu_link_hash_table *htab)
{
  return (s != htab->stub
	  && s->output_section != NULL
	  && s->output_section->owner == obfd
	  && ((s->flags & (SEC_ALLOC | SEC_LOAD | SEC_CODE))
	      == (SEC_ALLOC | SEC_LOAD | SEC_CODE))
	  && s->size != 0);
}