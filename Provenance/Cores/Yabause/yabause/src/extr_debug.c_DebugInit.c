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
struct TYPE_5__ {char* string; void (* callback ) (char*) ;int /*<<< orphan*/  stream; } ;
struct TYPE_6__ {int output_type; TYPE_1__ output; int /*<<< orphan*/ * name; } ;
typedef  int DebugOutType ;
typedef  TYPE_2__ Debug ;

/* Variables and functions */
#define  DEBUG_CALLBACK 132 
#define  DEBUG_STDERR 131 
#define  DEBUG_STDOUT 130 
#define  DEBUG_STREAM 129 
#define  DEBUG_STRING 128 
 int /*<<< orphan*/  fopen (char*,char*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

Debug * DebugInit(const char * n, DebugOutType t, char * s) {
	Debug * d;

        if ((d = (Debug *) malloc(sizeof(Debug))) == NULL)
           return NULL;

	d->output_type = t;

        if ((d->name = strdup(n)) == NULL)
        {
           free(d);
           return NULL;
        }

	switch(t) {
	case DEBUG_STREAM:
                d->output.stream = fopen(s, "w");
		break;
	case DEBUG_STRING:
		d->output.string = s;
		break;
	case DEBUG_STDOUT:
		d->output.stream = stdout;
		break;
	case DEBUG_STDERR:
		d->output.stream = stderr;
		break;
        case DEBUG_CALLBACK:
                d->output.callback = (void  (*) (char*))s;
	        break;
	}

	return d;
}