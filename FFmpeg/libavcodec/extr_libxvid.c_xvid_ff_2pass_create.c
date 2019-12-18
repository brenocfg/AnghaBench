#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ param; } ;
typedef  TYPE_2__ xvid_plg_create_t ;
struct xvid_ff_pass1 {TYPE_1__* context; } ;
struct TYPE_4__ {char* twopassbuffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_CAT (char*) ; 
 int /*<<< orphan*/  BUFFER_REMAINING (char*) ; 
 int XVID_ERR_FAIL ; 
 int /*<<< orphan*/  XVID_VERSION ; 
 int XVID_VERSION_MAJOR (int /*<<< orphan*/ ) ; 
 int XVID_VERSION_MINOR (int /*<<< orphan*/ ) ; 
 int XVID_VERSION_PATCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int xvid_ff_2pass_create(xvid_plg_create_t *param, void **handle)
{
    struct xvid_ff_pass1 *x = (struct xvid_ff_pass1 *) param->param;
    char *log = x->context->twopassbuffer;

    /* Do a quick bounds check */
    if (!log)
        return XVID_ERR_FAIL;

    /* We use snprintf() */
    /* This is because we can safely prevent a buffer overflow */
    log[0] = 0;
    snprintf(log, BUFFER_REMAINING(log),
             "# ffmpeg 2-pass log file, using xvid codec\n");
    snprintf(BUFFER_CAT(log), BUFFER_REMAINING(log),
             "# Do not modify. libxvidcore version: %d.%d.%d\n\n",
             XVID_VERSION_MAJOR(XVID_VERSION),
             XVID_VERSION_MINOR(XVID_VERSION),
             XVID_VERSION_PATCH(XVID_VERSION));

    *handle = x->context;
    return 0;
}