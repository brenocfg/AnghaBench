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
struct dtparam_state {char const* override_value; int /*<<< orphan*/ * used_props; } ;
typedef  int /*<<< orphan*/  STRING_VEC_T ;
typedef  int /*<<< orphan*/  DTBLOB_T ;

/* Variables and functions */
 int /*<<< orphan*/  FDT_ERR_NOSPACE ; 
 int NON_FATAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtoverlay_error (char*) ; 
 int dtoverlay_foreach_override_target (int /*<<< orphan*/ *,char const*,void*,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  dtparam_callback ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (void*,char const*,int) ; 

int dtparam_apply(DTBLOB_T *dtb, const char *override_name,
		  const char *override_data, int data_len,
		  const char *override_value, STRING_VEC_T *used_props)
{
    struct dtparam_state state;
    void *data;
    int err;

    state.used_props = used_props;
    state.override_value = override_value;

    /* Copy the override data in case it moves */
    data = malloc(data_len);
    if (data)
    {
	memcpy(data, override_data, data_len);
	err = dtoverlay_foreach_override_target(dtb, override_name,
						data, data_len,
						dtparam_callback,
						(void *)&state);
	free(data);
    }
    else
    {
	dtoverlay_error("out of memory");
	err = NON_FATAL(FDT_ERR_NOSPACE);
    }

    return err;
}