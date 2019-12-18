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
typedef  TYPE_1__* gss_buffer_t ;
typedef  int /*<<< orphan*/  gss_OID ;
struct TYPE_3__ {int /*<<< orphan*/ * value; scalar_t__ length; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
#define  GSS_C_GSS_CODE 129 
#define  GSS_C_MECH_CODE 128 
 scalar_t__ GSS_LAST ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 char const** min_err_table ; 
 void* strdup (char const*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 

OM_uint32 gss_display_status(OM_uint32 *min,
                             OM_uint32 status_value,
                             int status_type,
                             const gss_OID mech_type,
                             OM_uint32 *message_context,
                             gss_buffer_t status_string)
{
  const char maj_str[] = "Stub GSS error";
  (void)mech_type;
  if(min)
    *min = 0;

  if(message_context)
    *message_context = 0;

  if(status_string) {
    status_string->value = NULL;
    status_string->length = 0;

    if(status_value >= GSS_LAST)
      return GSS_S_FAILURE;

    switch(status_type) {
      case GSS_C_GSS_CODE:
        status_string->value = strdup(maj_str);
        break;
      case GSS_C_MECH_CODE:
        status_string->value = strdup(min_err_table[status_value]);
        break;
      default:
        return GSS_S_FAILURE;
    }

    if(status_string->value)
      status_string->length = strlen(status_string->value);
    else
      return GSS_S_FAILURE;
  }

  return GSS_S_COMPLETE;
}