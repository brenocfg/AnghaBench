#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ pipe_input; } ;
struct TYPE_5__ {char* prompt_buf; char* prompt; void* percent; } ;
typedef  TYPE_1__ MY_OBJ ;
typedef  int /*<<< orphan*/  DIALOG_CALLBACK ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int FALSE ; 
 int /*<<< orphan*/  MY_LEN ; 
 int TRUE ; 
 void* atoi (char*) ; 
 scalar_t__ decode_percent (char*) ; 
 int /*<<< orphan*/  delink (TYPE_1__*) ; 
 TYPE_3__ dialog_state ; 
 int /*<<< orphan*/  dlg_remove_callback (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 scalar_t__ feof (scalar_t__) ; 
 scalar_t__ ferror (scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isMarker (char*) ; 
 int read_data (char*,scalar_t__) ; 
 int /*<<< orphan*/  repaint_text (TYPE_1__*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static bool
handle_input(DIALOG_CALLBACK * cb)
{
    MY_OBJ *obj = (MY_OBJ *) cb;
    bool result;
    bool cleanup = FALSE;
    int status;
    char buf[MY_LEN + 1];

    if (dialog_state.pipe_input == 0) {
	status = -1;
	cleanup = TRUE;
    } else if ((status = read_data(buf, dialog_state.pipe_input)) > 0) {

	if (isMarker(buf)) {
	    /*
	     * Historically, next line should be percentage, but one of the
	     * worse-written clones of 'dialog' assumes the number is missing.
	     * (Gresham's Law applied to software).
	     */
	    if ((status = read_data(buf, dialog_state.pipe_input)) > 0) {

		obj->prompt_buf[0] = '\0';
		if (decode_percent(buf))
		    obj->percent = atoi(buf);
		else
		    strcpy(obj->prompt_buf, buf);

		/* Rest is message text */
		while ((status = read_data(buf, dialog_state.pipe_input)) > 0
		       && !isMarker(buf)) {
		    if (strlen(obj->prompt_buf) + strlen(buf) <
			sizeof(obj->prompt_buf) - 1) {
			strcat(obj->prompt_buf, buf);
		    }
		}

		if (obj->prompt != obj->prompt_buf)
		    free(obj->prompt);
		obj->prompt = obj->prompt_buf;
	    }
	} else if (decode_percent(buf)) {
	    obj->percent = atoi(buf);
	}
    } else {
	if (feof(dialog_state.pipe_input) ||
	    (ferror(dialog_state.pipe_input) && errno != EINTR)) {
	    cleanup = TRUE;
	}
    }

    repaint_text(obj);
    if (status > 0) {
	result = TRUE;
    } else {
	result = FALSE;
	if (cleanup) {
	    dlg_remove_callback(cb);
	    delink(obj);
	}
    }

    return result;
}