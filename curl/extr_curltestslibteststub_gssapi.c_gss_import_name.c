#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gss_name_t ;
typedef  TYPE_1__* gss_buffer_t ;
typedef  int /*<<< orphan*/  gss_OID ;
struct TYPE_3__ {int /*<<< orphan*/  length; int /*<<< orphan*/  value; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_INVALID_ARGS ; 
 scalar_t__ GSS_NO_MEMORY ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 char* strndup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

OM_uint32 gss_import_name(OM_uint32 *min,
                          const gss_buffer_t input_name_buffer,
                          const gss_OID input_name_type,
                          gss_name_t *output_name)
{
  char *name = NULL;
  (void)input_name_type;

  if(!min)
    return GSS_S_FAILURE;

  if(!input_name_buffer || !output_name) {
    *min = GSS_INVALID_ARGS;
    return GSS_S_FAILURE;
  }

  name = strndup(input_name_buffer->value, input_name_buffer->length);
  if(!name) {
    *min = GSS_NO_MEMORY;
    return GSS_S_FAILURE;
  }

  *output_name = (gss_name_t) name;
  *min = 0;

  return GSS_S_COMPLETE;
}