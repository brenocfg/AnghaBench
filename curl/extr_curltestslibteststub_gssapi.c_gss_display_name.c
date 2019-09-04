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
typedef  int /*<<< orphan*/  gss_const_name_t ;
typedef  int /*<<< orphan*/  gss_buffer_t ;
typedef  int /*<<< orphan*/  gss_OID ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_S_FAILURE ; 

OM_uint32 gss_display_name(OM_uint32 *min,
                           gss_const_name_t input_name,
                           gss_buffer_t output_name_buffer,
                           gss_OID *output_name_type)
{
  (void)min;
  (void)input_name;
  (void)output_name_buffer;
  (void)output_name_type;
  return GSS_S_FAILURE;
}