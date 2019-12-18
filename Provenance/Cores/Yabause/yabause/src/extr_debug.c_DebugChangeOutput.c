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
struct TYPE_4__ {char* string; void (* callback ) (char*) ;scalar_t__ stream; } ;
struct TYPE_5__ {int output_type; TYPE_1__ output; } ;
typedef  int DebugOutType ;
typedef  TYPE_2__ Debug ;

/* Variables and functions */
#define  DEBUG_CALLBACK 132 
#define  DEBUG_STDERR 131 
#define  DEBUG_STDOUT 130 
#define  DEBUG_STREAM 129 
#define  DEBUG_STRING 128 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 scalar_t__ fopen (char*,char*) ; 
 scalar_t__ stderr ; 
 scalar_t__ stdout ; 

void DebugChangeOutput(Debug * d, DebugOutType t, char * s) {
	if (t != d->output_type) {
		if (d->output_type == DEBUG_STREAM)
                {
                   if (d->output.stream)
			fclose(d->output.stream);
                }
		d->output_type = t;
	}
	switch(t) {
	case DEBUG_STREAM:
		d->output.stream = fopen(s, "w");
		break;
	case DEBUG_STRING:
		d->output.string = s;
		break;
	case DEBUG_CALLBACK:
                  d->output.callback = (void  (*) (char*))s;
		  break;
	case DEBUG_STDOUT:
		d->output.stream = stdout;
		break;
	case DEBUG_STDERR:
		d->output.stream = stderr;
		break;
	}
}