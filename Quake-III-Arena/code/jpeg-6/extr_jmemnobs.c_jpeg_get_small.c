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
struct TYPE_2__ {scalar_t__ (* Malloc ) (size_t) ;} ;

/* Variables and functions */
 TYPE_1__ ri ; 
 scalar_t__ stub1 (size_t) ; 

void *
jpeg_get_small (j_common_ptr cinfo, size_t sizeofobject)
{
  return (void *) ri.Malloc(sizeofobject);
}