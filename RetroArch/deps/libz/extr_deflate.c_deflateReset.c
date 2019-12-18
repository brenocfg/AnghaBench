#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* z_streamp ;
typedef  int /*<<< orphan*/  deflate_state ;
struct TYPE_4__ {scalar_t__ state; } ;

/* Variables and functions */
 int Z_OK ; 
 int deflateResetKeep (TYPE_1__*) ; 
 int /*<<< orphan*/  lm_init (int /*<<< orphan*/ *) ; 

int deflateReset (z_streamp strm)
{
   int ret;

   ret = deflateResetKeep(strm);
   if (ret == Z_OK)
      lm_init((deflate_state*)strm->state);
   return ret;
}