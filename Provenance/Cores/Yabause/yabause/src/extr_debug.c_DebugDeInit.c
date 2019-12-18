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
struct TYPE_5__ {int /*<<< orphan*/  stream; } ;
struct TYPE_6__ {int output_type; struct TYPE_6__* name; TYPE_1__ output; } ;
typedef  TYPE_2__ Debug ;

/* Variables and functions */
#define  DEBUG_CALLBACK 132 
#define  DEBUG_STDERR 131 
#define  DEBUG_STDOUT 130 
#define  DEBUG_STREAM 129 
#define  DEBUG_STRING 128 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

void DebugDeInit(Debug * d) {
        if (d == NULL)
           return;

	switch(d->output_type) {
	case DEBUG_STREAM:
                if (d->output.stream)
                   fclose(d->output.stream);
		break;
	case DEBUG_STRING:
	case DEBUG_STDOUT:
	case DEBUG_STDERR:
	case DEBUG_CALLBACK:
		break;
	}
        if (d->name)
           free(d->name);
	free(d);
}