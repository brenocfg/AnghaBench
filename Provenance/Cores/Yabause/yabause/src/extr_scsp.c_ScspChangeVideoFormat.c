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
struct TYPE_2__ {int /*<<< orphan*/  (* ChangeVideoFormat ) (int) ;} ;

/* Variables and functions */
 TYPE_1__* SNDCore ; 
 scalar_t__ scsp_alloc_bufs () ; 
 int scsplines ; 
 int scspsoundbufs ; 
 int scspsoundbufsize ; 
 int scspsoundlen ; 
 int /*<<< orphan*/  stub1 (int) ; 

int
ScspChangeVideoFormat (int type)
{
  scspsoundlen = 44100 / (type ? 50 : 60);
  scsplines = type ? 313 : 263;
  scspsoundbufsize = scspsoundlen * scspsoundbufs;

  if (scsp_alloc_bufs () < 0)
    return -1;

  SNDCore->ChangeVideoFormat (type ? 50 : 60);

  return 0;
}