#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ json_error_t ;
struct TYPE_6__ {scalar_t__ state; } ;
typedef  TYPE_2__ hb_state_t ;
typedef  int /*<<< orphan*/  hb_handle_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 scalar_t__ HB_STATE_SCANNING ; 
 int /*<<< orphan*/  hb_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_get_state2 (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  hb_scan (int /*<<< orphan*/ *,char const*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_snooze (int) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * hb_value_json (char const*) ; 
 int json_unpack_ex (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unpack_i (int*) ; 
 int /*<<< orphan*/  unpack_s (char const**) ; 

void hb_json_job_scan( hb_handle_t * h, const char * json_job )
{
    hb_dict_t * dict;
    int result;
    json_error_t error;

    dict = hb_value_json(json_job);

    int title_index;
    const char *path = NULL;

    result = json_unpack_ex(dict, &error, 0, "{s:{s:s, s:i}}",
                            "Source",
                                "Path",     unpack_s(&path),
                                "Title",    unpack_i(&title_index)
                           );
    if (result < 0)
    {
        hb_error("json unpack failure, failed to find title: %s", error.text);
        hb_value_free(&dict);
        return;
    }

    // If the job wants to use Hardware decode, it must also be
    // enabled during scan.  So enable it here.
    hb_scan(h, path, title_index, -1, 0, 0);

    // Wait for scan to complete
    hb_state_t state;
    hb_get_state2(h, &state);
    while (state.state == HB_STATE_SCANNING)
    {
        hb_snooze(50);
        hb_get_state2(h, &state);
    }
    hb_value_free(&dict);
}