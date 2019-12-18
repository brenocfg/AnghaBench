#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct syscall {TYPE_2__* tp_format; } ;
struct format_field {int name; struct format_field* next; } ;
struct TYPE_3__ {struct format_field* fields; } ;
struct TYPE_4__ {TYPE_1__ format; } ;

/* Variables and functions */
 scalar_t__ scnprintf (char*,size_t,char*,char*,int,unsigned long) ; 

__attribute__((used)) static size_t syscall__scnprintf_args(struct syscall *sc, char *bf, size_t size,
				      unsigned long *args)
{
	int i = 0;
	size_t printed = 0;

	if (sc->tp_format != NULL) {
		struct format_field *field;

		/* No need to skip 'nr' field, since it's not in RHEL6 yet. */
		for (field = sc->tp_format->format.fields; field; field = field->next) {
			printed += scnprintf(bf + printed, size - printed,
					     "%s%s: %ld", printed ? ", " : "",
					     field->name, args[i++]);
		}
	} else {
		while (i < 6) {
			printed += scnprintf(bf + printed, size - printed,
					     "%sarg%d: %ld",
					     printed ? ", " : "", i, args[i]);
			++i;
		}
	}

	return printed;
}