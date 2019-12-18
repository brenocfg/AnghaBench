#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ type; } ;
typedef  TYPE_1__ tdata_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_7__ {int /*<<< orphan*/  start_address; } ;
typedef  TYPE_2__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  srec_write_record (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
srec_write_terminator (bfd *abfd, tdata_type *tdata)
{
  return srec_write_record (abfd, 10 - tdata->type,
			    abfd->start_address, NULL, NULL);
}