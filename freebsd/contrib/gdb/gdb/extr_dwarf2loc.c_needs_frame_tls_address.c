#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct needs_frame_baton {int needs_frame; } ;
typedef  int CORE_ADDR ;

/* Variables and functions */

__attribute__((used)) static CORE_ADDR
needs_frame_tls_address (void *baton, CORE_ADDR offset)
{
  struct needs_frame_baton *nf_baton = baton;
  nf_baton->needs_frame = 1;
  return 1;
}