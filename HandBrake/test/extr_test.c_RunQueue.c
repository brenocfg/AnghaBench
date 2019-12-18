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
typedef  int /*<<< orphan*/  hb_value_t ;
typedef  int /*<<< orphan*/  hb_handle_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 scalar_t__ HB_VALUE_TYPE_ARRAY ; 
 scalar_t__ HB_VALUE_TYPE_DICT ; 
 int RunQueueJob (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ die ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  hb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * hb_value_array_get (int /*<<< orphan*/ *,int) ; 
 int hb_value_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_value_read_json (char const*) ; 
 scalar_t__ hb_value_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

int RunQueue(hb_handle_t *h, const char *queue_import_name)
{
    hb_value_t * queue = hb_value_read_json(queue_import_name);

    if (hb_value_type(queue) == HB_VALUE_TYPE_DICT)
    {
        return RunQueueJob(h, hb_dict_get(queue, "Job"));
    }
    else if (hb_value_type(queue) == HB_VALUE_TYPE_ARRAY)
    {
        int ii, count, result = 0;

        count = hb_value_array_len(queue);
        for (ii = 0; ii < count; ii++)
        {
            hb_dict_t * entry = hb_value_array_get(queue, ii);
            int ret = RunQueueJob(h, hb_dict_get(entry, "Job"));
            if (ret < 0)
            {
                result = ret;
            }
            if (die)
            {
                break;
            }
        }
        return result;
    }
    else
    {
        fprintf(stderr, "Error: Invalid queue file %s\n", queue_import_name);
        return -1;
    }
    return 0;
}