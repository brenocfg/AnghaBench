#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  j_common_ptr ;
struct TYPE_2__ {int /*<<< orphan*/  (* Free ) (void*) ;} ;

/* Variables and functions */
 TYPE_1__ ri ; 
 int /*<<< orphan*/  stub1 (void*) ; 

void
jpeg_free_small (j_common_ptr cinfo, void * object, size_t sizeofobject)
{
  ri.Free(object);
}