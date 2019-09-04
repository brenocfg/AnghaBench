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
typedef  int /*<<< orphan*/  gss_name_t ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_S_COMPLETE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

OM_uint32 gss_release_name(OM_uint32 *min,
                           gss_name_t *input_name)
{
  if(min)
    *min = 0;

  if(input_name)
    free(*input_name);

  return GSS_S_COMPLETE;
}