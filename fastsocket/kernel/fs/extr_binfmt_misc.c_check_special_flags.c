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
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 int MISC_FMT_CREDENTIALS ; 
 int MISC_FMT_OPEN_BINARY ; 
 int MISC_FMT_PRESERVE_ARGV0 ; 

__attribute__((used)) static char * check_special_flags (char * sfs, Node * e)
{
	char * p = sfs;
	int cont = 1;

	/* special flags */
	while (cont) {
		switch (*p) {
			case 'P':
				p++;
				e->flags |= MISC_FMT_PRESERVE_ARGV0;
				break;
			case 'O':
				p++;
				e->flags |= MISC_FMT_OPEN_BINARY;
				break;
			case 'C':
				p++;
				/* this flags also implies the
				   open-binary flag */
				e->flags |= (MISC_FMT_CREDENTIALS |
						MISC_FMT_OPEN_BINARY);
				break;
			default:
				cont = 0;
		}
	}

	return p;
}