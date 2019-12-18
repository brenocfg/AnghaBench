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
typedef  scalar_t__ edge ;

/* Variables and functions */
 scalar_t__ mfb_kj_edge ; 

__attribute__((used)) static bool
mfb_keep_just (edge e)
{
  return e != mfb_kj_edge;
}